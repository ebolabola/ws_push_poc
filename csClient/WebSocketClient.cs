using Google.Protobuf;
using proto.PushService;
using PushPresenceService;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Net.WebSockets;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace csClient
{
    interface IPushEvents
    {
        void Handle(PrescencePushData msg);
    }

    public class WebSocketClient:
        IPushEvents
    {
        private Uri _uri;
        private ClientWebSocket _ws;
        private CancellationTokenSource _connectToken;
        private Task _wsTaskConnnect;

        private CancellationTokenSource _recieveToken;
        private Task _wsTaskRecieve;
        public WebSocketClient(Uri uri)
        {
            _uri = uri;
        }
        public async Task Start(WSClientData data)
        {
            _ws = new ClientWebSocket();

            var buf = new byte[data.CalculateSize()];
            var st = new CodedOutputStream(buf);
            data.WriteTo(st);

            var hdr = System.Convert.ToBase64String(buf);
            _ws.Options.SetRequestHeader("WSDATA", hdr);

            await _ws.ConnectAsync(_uri, CancellationToken.None);
            _connectToken = new CancellationTokenSource();
            _wsTaskConnnect = Task.Run(CreateConnection);
        }
        private async Task CreateConnection()
        {
            var data = await ReceiveMessage(_connectToken.Token);
            if (data != null)
            {
                Token = PUSH_TOKEN.Parser.ParseFrom(data);
                _connectToken = null;
                _wsTaskConnnect = null;

                _recieveToken = new CancellationTokenSource();
                _wsTaskRecieve = Task.Run(Recieve);
            }
        }

 
        private async Task Recieve()
        {
            var buffer = new byte[255];
            var seg = new ArraySegment<byte>(buffer);
            var msgbuffer = new List<byte>();
            while (true)
            {
                try
                {
                    var data = await ReceiveMessage(_recieveToken.Token);
                    if (data != null)
                    {
                        using (var st = new MemoryStream(data))
                        {
                            BinaryReader reader = new BinaryReader(st);
                            int hdrsize = reader.ReadInt32();
                            var hdr = MessageHeader.Parser.ParseFrom(data, sizeof(int), hdrsize);
                            switch (hdr.MessageType)
                            {
                                case PushMessageType.PresenceService:
                                    var pr = PrescencePushData.Parser.ParseFrom(data, sizeof(int) + hdrsize, data.Length - (sizeof(int) + hdrsize));
                                    Handle(pr);
                                    break;
                            }
                        }
                    }
                    if (_recieveToken.Token.IsCancellationRequested)
                        break;
                }
                catch (Exception e)
                {

                }
            }
        }
        public async Task Stop()
        {
            if (_connectToken != null)
            {
                _connectToken.Cancel();
                await _wsTaskConnnect;
                _connectToken = null;
                _wsTaskConnnect = null;
            }

            if (_recieveToken != null)
            {
                _recieveToken.Cancel();
                await _wsTaskRecieve;
                _recieveToken = null;
                _wsTaskRecieve = null;
            }

        }

        private async Task<byte[]> ReceiveMessage(CancellationToken token)
        {
            var buffer = new byte[255];
            var seg = new ArraySegment<byte>(buffer);
            var msgbuffer = new List<byte>();

            while (true)
            {

                WebSocketReceiveResult result = await _ws.ReceiveAsync(buffer, token);
                if (result.Count > 0)
                    msgbuffer.AddRange(seg.Slice(0, result.Count));
                if (result.EndOfMessage)
                {
                    return msgbuffer.ToArray();
                }
                if (_connectToken.Token.IsCancellationRequested)
                    break;
            }
            return null;
        }


        public void Handle(PrescencePushData msg)
        {
            Console.WriteLine($"{msg.Version}-{msg.Kuku}-{msg.Dummy}");
        }

        public PUSH_TOKEN Token
        {
            get;
            private set;
        }

    }
}
