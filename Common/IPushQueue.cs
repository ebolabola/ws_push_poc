using Backend.Common.EntitySync.RMQ;
using Google.Protobuf;
using proto.PushService;
using System;
using System.Collections.Concurrent;
using System.IO;
using System.Threading.Tasks;

namespace Common
{
    public interface IPushQueue<T> where T : IMessage
    {
        void Enqueue(PUSH_TOKEN token, T t);
    }



    public class PushQueue<T> : IPushQueue<T> where T : IMessage
    {
        private string _connectionString;
        private PushMessageType _pushMessageType;
        private RabbitQueue _queue;
        ConcurrentDictionary<Int32, RabbitQueue> _quues = new ConcurrentDictionary<Int32, RabbitQueue>();

        public PushQueue(string connectionString, PushMessageType pushMessageType)
        {
            _connectionString = connectionString;
            _pushMessageType = pushMessageType;
        }

        public void Enqueue(PUSH_TOKEN token, T t)
        {
            var q = _quues.GetOrAdd(token.InstanceKey, (key) =>
            {
                var queue = RabbitQueue.CreateSender(_connectionString, "pushqueue", $"{token.InstanceKey}");
                queue.Start();
                return queue;
            });

            using (var st = new MemoryStream())
            {
                var hdr = new MessageHeader()
                {
                    Token = token,
                    MessageType = _pushMessageType,
                };
                BinaryWriter writer = new BinaryWriter(st);
                writer.Write(hdr.CalculateSize());
                hdr.WriteTo(st);
                t.WriteTo(st);
                q.Send(st.ToArray());
            }
        }
    }
}
