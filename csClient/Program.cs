using Google.Protobuf;
using proto.PushService;
using System;
using System.IO;
using System.Net.WebSockets;
using System.Threading;

namespace csClient
{
    class Program
    {
        static void Main(string[] args)
        {
            var ws = new ClientWebSocket();
            CancellationTokenSource ct = new CancellationTokenSource();
            try
            {
                WSClientData data = new WSClientData();
                data.Generation = 1;
                data.UserId = "UserId";
                data.Signature = "Signature";

                var buf = new byte[data.CalculateSize()];
                var st = new CodedOutputStream(buf) ;
                data.WriteTo(st);

                var hdr = System.Convert.ToBase64String(buf);
                ws.Options.SetRequestHeader("WSDATA", hdr);
                ws.ConnectAsync(new Uri("ws://localhost:56566/ws"), ct.Token).Wait();
            }
            catch (Exception e)
            {

            }
        }
    }
}
