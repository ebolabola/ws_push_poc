using Backend.Common.EntitySync.RMQ;
using Common;
using Google.Protobuf;
using proto.PushService;
using PushPresenceService;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Threading.Tasks;

namespace PushService
{
    public class PushQueueReciever
    {
        private PushMessageType _pushMessageType;
        private IConnectionManager _connectionManager;
        private RabbitQueue _queue;

        public PushQueueReciever(string connectionString, int instanceKey, IConnectionManager connectionManager, PushMessageType pushMessageType, ILogger logger)
        {
            _pushMessageType = pushMessageType;
            _connectionManager = connectionManager;
            _queue = RabbitQueue.CreateReciever(connectionString, "pushqueue", $"{instanceKey}", OnRecieve);
            
        }

        public void Start()
        {
            _queue.Start();
        }

        public void Stop()
        {
            _queue.Stop();
        }


        void OnRecieve(byte[] data)
        {
            var clientData = new byte[data.Length];
            Array.Copy(data, clientData, data.Length);
            using (var st = new MemoryStream(data))
            {
                BinaryReader reader = new BinaryReader(st);
                int hdrsize = reader.ReadInt32();
                var hdr = MessageHeader.Parser.ParseFrom(data, sizeof(int), hdrsize);
                //var pr = PrescencePushData.Parser.ParseFrom(data, sizeof(int) + hdrsize, data.Length - (sizeof(int) + hdrsize));
                _connectionManager.DispatchMessage(hdr.Token, clientData);
            }
        }

  
    }
}
