using Common;
using Google.Protobuf;
using Microsoft.AspNetCore.Http;
using proto.PushService;
using System;
using System.Collections.Concurrent;
using System.IO;
using System.Linq;
using System.Net.WebSockets;
using System.Threading;
using System.Threading.Tasks;

namespace PushService
{

    public class PushMiddleware
    {
        private Func<HttpContext, Task> _processor;
        private RequestDelegate _next;
        private IConnectionManager _connectionManager;

        public PushMiddleware(
           IConnectionManager connectionManager,
           RequestDelegate next)
        {
            _next = next;
            _connectionManager = connectionManager;
        }


        public async Task Invoke(HttpContext context)
        {
            if (!context.WebSockets.IsWebSocketRequest)
            {
                await _next(context);
                return;
            }
   
            using (var socket = await context.WebSockets.AcceptWebSocketAsync())
            {
                await _connectionManager.HandleConnection(socket, context);
            }
        }

    }


    public interface IConnectionManager
    {
        Task HandleConnection(WebSocket socket, HttpContext httpContext);
        void DispatchMessage(PUSH_TOKEN tk, byte[] data);
        void OnUserConnected(ClientConnected clientConnected);
        void OnInstacneHeartbeat(InstanceHeartBeat instanceHeartbeat);
    }



    public class ConnectionManager: IConnectionManager
    {
        private int _instanceKey;
        private Guid _instanceId;
        private Logger _logger;

        private class WebSocketData
        {
            public string UserId;
            public string Signature;
            public int Generation;
            public int ClientKey;
            public CancellationTokenSource ReciveToken;
            public DateTime LastUpdated;
            public DateTime? RecieveFailed;
            public ConcurrentQueue<byte[]> Messages = new ConcurrentQueue<byte[]>();
        }
        private ConcurrentDictionary<WebSocket, WebSocketData> _connections = new ConcurrentDictionary<WebSocket, WebSocketData>();
        private ConcurrentDictionary<int, WebSocket> _clients = new ConcurrentDictionary<int, WebSocket>();
        private ConcurrentDictionary<string, WebSocketData> _failedClients = new ConcurrentDictionary<string, WebSocketData>();
        private ConcurrentQueue<(WebSocket socket, WebSocketData data)> _pending = new ConcurrentQueue<(WebSocket socket, WebSocketData data)>();
        private PushQueueReciever _queueRiceReciever;
        private PushInstanceSync _pushInstanceSync;
        private CancellationTokenSource _timeOutToken;
        private Task _timeOutTask;

        public ConnectionManager(Guid instanceId, string connectionString, ILogger logger)
        {
            _instanceKey = instanceId.GetHashCode();
            _instanceId = instanceId;
            _logger = new Logger();
            _queueRiceReciever = new PushQueueReciever(connectionString, _instanceKey, this, PushMessageType.PresenceService, _logger);
            _pushInstanceSync = new PushInstanceSync(connectionString, _instanceId,this, _logger);

        }

        public void Start()
        {
            _queueRiceReciever.Start();
            _pushInstanceSync.Start();
            _timeOutToken = new CancellationTokenSource();
            _timeOutTask = Task.Run(TimeoutTask);

        }

        public void Stop()
        {
            _queueRiceReciever.Stop();
            _pushInstanceSync.Stop();

        }

        public async Task HandleConnection(WebSocket socket, HttpContext httpContext)
        {
            if (!httpContext.Request.Headers.TryGetValue("WSDATA", out var hdr))
                return;

            if (_connections.TryGetValue(socket, out var wd ))
                return;

            var data = System.Convert.FromBase64String(hdr);
            WSClientData wsData = WSClientData.Parser.ParseFrom(data);


            if (_failedClients.TryRemove(wsData.UserId, out var wsd))
            {
                _logger.LogInformation("Client reconnect UserId: {0}", wsData.UserId);
            }

            PUSH_TOKEN tk = new PUSH_TOKEN();
            var clientKey = $"{wsData.UserId}{wsData.Signature}{wsData.Generation}".GetHashCode();
            tk.InstanceKey = _instanceKey;
            tk.ClientKey = clientKey;
            using (var st = new MemoryStream())
            {
                tk.WriteTo(st);
                var ct = new CancellationTokenSource();
                await socket.SendAsync(new ReadOnlyMemory<byte>(st.ToArray()), WebSocketMessageType.Binary, true, ct.Token);
            }
            var recievToken = new CancellationTokenSource();

            wsd = new WebSocketData()
            {
                UserId = wsData.UserId,
                Signature = wsData.Signature,
                Generation = wsData.Generation,
                ClientKey = clientKey,
                ReciveToken = recievToken,
                LastUpdated = DateTime.UtcNow,
            };
            _connections.TryAdd(socket, wsd);
            _clients.TryAdd(clientKey, socket);
            _pushInstanceSync.SendUserConnected(wsData);

            var buffer = new byte[32];
            while (!recievToken.IsCancellationRequested)
            {
                try
                {
                    var result = await socket.ReceiveAsync(new ArraySegment<byte>(buffer), recievToken.Token);
                    ClientPing.Parser.ParseFrom(buffer,0, result.Count);
                    wsd.LastUpdated = DateTime.UtcNow;
                }
                catch (Exception e)
                {
                    wsd.RecieveFailed = DateTime.UtcNow;

                    if (socket.State == WebSocketState.Open || socket.State == WebSocketState.CloseReceived || socket.State == WebSocketState.CloseSent)
                        await socket.CloseAsync(WebSocketCloseStatus.NormalClosure, "Release", CancellationToken.None);

                    WebSocketData d = null;
                    _logger.LogInformation("Client error UserId: {0}", wsData.UserId);
                    _connections.TryRemove(socket, out d);
                    _clients.TryRemove(clientKey, out socket);
                    _failedClients.TryAdd(wsd.UserId, wsd);
                    break;
                }
            }
        }

        public async Task AddConnection(WebSocket socket, HttpContext httpContext)
        {
            if (httpContext.Request.Headers.TryGetValue("WSDATA", out var hdr))
            {
                var data = System.Convert.FromBase64String(hdr);
                WSClientData wsData = WSClientData.Parser.ParseFrom(data);
                PUSH_TOKEN tk = new PUSH_TOKEN();
                tk.InstanceKey = _instanceKey;
                tk.ClientKey = $"{wsData.UserId}{wsData.Signature}{wsData.Generation}".GetHashCode();
                using (var st = new MemoryStream())
                {
                    tk.WriteTo(st);
                    var ct = new CancellationTokenSource();
                    await socket.SendAsync(new ReadOnlyMemory<byte>(st.ToArray()), WebSocketMessageType.Binary, false, ct.Token);
                }
            }
        }

        public void DispatchMessage(PUSH_TOKEN tk, byte[] data)
        {
            if ( _clients.TryGetValue(tk.ClientKey, out var s))
            {
                if (_connections.TryGetValue(s, out var wd))
                {
                    wd.Messages.Enqueue(data);
                    var t = Task.Run(async () =>
                    {
                        while (wd.Messages.TryPeek(out var data))
                        {
                            await s.SendAsync(data, WebSocketMessageType.Binary, true, CancellationToken.None);
                            wd.Messages.TryDequeue(out data);
                        }
                    }).ContinueWith(t =>
                    {
                        if (t.Exception != null)
                        {

                        }
                    });
                }
            }
        }

        public Task TimeoutTask()
        {
            try
            {
                while (true)
                {
 
                    Task.WaitAny(new Task[] { Task.Delay(1000) }, _timeOutToken.Token);
                    if (_timeOutToken.IsCancellationRequested)
                        break;
                    var clients = _failedClients.Where(cl => (cl.Value.RecieveFailed.HasValue && (DateTime.UtcNow - cl.Value.RecieveFailed) > TimeSpan.FromSeconds(10))).ToList();
                    {
                        clients.ForEach(cl =>
                        {
                            _logger.LogInformation("Client finaly disconected UserId: {0}", cl.Key);
                        });
                        clients.ForEach(cl =>
                        {
                            _failedClients.TryRemove(cl.Key, out var w);
                        });
                    }
                }
            }
            catch (Exception)
            {

            }
            return Task.CompletedTask;
        }
        public void OnUserConnected(ClientConnected clientConnected)
        {
            _failedClients.TryRemove(clientConnected.ClientData.UserId, out var cd);
        }

        public void OnInstacneHeartbeat(InstanceHeartBeat instanceHeartbeat)
        {
            throw new NotImplementedException();
        }
    }
}
