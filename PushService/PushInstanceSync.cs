using Common;
using Google.Protobuf;
using proto.PushService;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Threading.Tasks;

namespace PushService
{
    public class PushInstanceSync
    {
        private IConnectionManager _connectionManager;
        private RabbitTopic _topic;

        public PushInstanceSync(string connectionString, Guid instanceKey, IConnectionManager connectionManager, ILogger logger)
        {
            _connectionManager = connectionManager;
            _topic =  new RabbitTopic(connectionString, "pushsync", logger, instanceKey);
            
        }
        public void SendUserConnected(WSClientData clientData)
        {
                var msg = new PushIntanceSyncMessage();
                _topic.Send(msg.ToByteArray());
        }
        public void Start()
        {
            _topic.Start(OnRecieve);
        }
        public void Stop()
        {
            _topic.Stop();
        }

        void OnRecieve(byte[] data)
        {
            var msg = PushIntanceSyncMessage.Parser.ParseFrom(data);
            if (msg.ClientConnected != null)
            {
                _connectionManager.OnUserConnected(msg.ClientConnected);
            }
            if (msg.InstanceHeartbeat != null)
            {
                _connectionManager.OnInstacneHeartbeat(msg.InstanceHeartbeat);
            }
        }
    }
}
