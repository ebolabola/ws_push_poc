using Google.Protobuf;
using Microsoft.AspNetCore.Connections;
using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Http.Connections;
using proto.PushService;
using ProtoBuf;
using System;
using System.Collections.Concurrent;
using System.Collections.Generic;
using System.ComponentModel;
using System.IO;
using System.Linq;
using System.Net.WebSockets;
using System.Security.Cryptography;
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

    }

    public class ConnectionManager: IConnectionManager
    {
        private int _instanceKey;
        private class WebSocketData
        {
            public string UserId;
            public string Signature;
            public int Generation;
            public int ClientKey;
            public CancellationTokenSource ReciveToken;
            public DateTime LastUpdated { get; internal set; }
            public ConcurrentQueue<byte[]> Messages = new ConcurrentQueue<byte[]>();
        }
        private ConcurrentDictionary<WebSocket, WebSocketData> _connections = new ConcurrentDictionary<WebSocket, WebSocketData>();
        private ConcurrentDictionary<int, WebSocket> _clients = new ConcurrentDictionary<int, WebSocket>();
        private ConcurrentQueue<(WebSocket socket, WebSocketData data)> _pending = new ConcurrentQueue<(WebSocket socket, WebSocketData data)>();

        public ConnectionManager(int instanceKey)
        {
            _instanceKey = instanceKey;
        }
        public async Task HandleConnection(WebSocket socket, HttpContext httpContext)
        {
            if (!httpContext.Request.Headers.TryGetValue("WSDATA", out var hdr))
                return;

            if (_connections.TryGetValue(socket, out var wd ))
                return;
            var data = System.Convert.FromBase64String(hdr);
            WSClientData wsData = WSClientData.Parser.ParseFrom(data);
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

            var wsd = new WebSocketData()
            {
                UserId = wsData.UserId,
                Signature = wsData.Signature,
                Generation = wsData.Generation,
                ClientKey = clientKey,
                ReciveToken = recievToken,
                LastUpdated = DateTime.UtcNow
            };
            _connections.TryAdd(socket, wsd);
            _clients.TryAdd(clientKey, socket);

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
                    break;
                }
            }
            if (socket.State == WebSocketState.Open || socket.State == WebSocketState.CloseReceived || socket.State == WebSocketState.CloseSent)
                await socket.CloseAsync(WebSocketCloseStatus.NormalClosure, "Release", CancellationToken.None);

            WebSocketData d = null;
            _connections.TryRemove(socket, out d);
            _clients.TryRemove(clientKey, out socket);
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
                            try
                            {
                                await s.SendAsync(data, WebSocketMessageType.Binary, true, CancellationToken.None);
                                wd.Messages.TryDequeue(out data);
                            }
                            catch (Exception e)
                            {

                            }
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
    }
}
