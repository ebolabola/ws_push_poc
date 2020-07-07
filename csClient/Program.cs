using Google.Protobuf;
using Grpc.Net.Client;
using interfaces;
using proto.PushService;
using System;
using System.IO;
using System.Net.WebSockets;
using System.Threading;
using WebSocketClient;

namespace csClient
{
    class Program
    {
        static void Main(string[] args)
        {
            try
            {
                var userId = "u1";
                var Generation = 1;
                var Signature = "sig1";
                var cl = new WSClient(new Uri("ws://localhost:56566/ws"));
                cl.Start(new WSClientData()
                {
                    Generation = Generation,
                    Signature = Signature,
                    UserId = userId
                }).Wait();



                using var channel = GrpcChannel.ForAddress("https://localhost:5001");
                var client = new interfaces.IPresenceService.IPresenceServiceClient (channel);
                var reply1 = client.PresenceConnect(new PresenceConnectRequest()
                {
                    UserId = userId,
                });

                var reply2 = client.PresenceGetStateAndSub(new PresenceGetStateAndSubRequest()
                {
                    UserId = userId,
                    Token = cl.Token,
                    
                });

                while (true)
                {
                    Thread.Sleep(100);
                }
            }
            catch (Exception e)
            {

            }
        }
    }
}
