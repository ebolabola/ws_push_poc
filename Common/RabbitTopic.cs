using RabbitMQ.Client;
using RabbitMQ.Client.Events;
using System;
using System.Collections.Concurrent;
using System.Collections.Generic;
using System.IO;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace Common
{
    public class RabbitTopic
    {
        private CancellationTokenSource _sendTocken;
        private Task _send;
        private Guid _instanceId;
        private string _connectionString;
        private string _topicName;
        private string _partition;
        private ILogger _logger;
        private IConnection _connection;
        private string _exchange;
        private IModel _channel;
        private EventingBasicConsumer _consumer;
        private ConcurrentQueue<byte[]> _queue = new ConcurrentQueue<byte[]>();

        public RabbitTopic(string connection, string topicName, ILogger logger, Guid instanceId)
        {
            _instanceId = instanceId;
            _connectionString = connection;
            _topicName = topicName;
            _logger = logger;
        }

        public void Start(Action<byte[]> OnRecieve)
        {
            var factory = new ConnectionFactory();
            factory.Uri = new Uri(_connectionString);
            _connection = factory.CreateConnection();
            _channel = _connection.CreateModel();
            _exchange = $"push_ex_{_topicName}";
            _channel.ExchangeDeclare(_exchange, "fanout", false, false);

            var args = new Dictionary<string, object>();
            args.Add("x-message-ttl", 20000);
            var _queueName = $"push_qe_{_partition}_{_instanceId}";
            _channel.QueueDeclare(_queueName, false, false, false, args);
            _channel.QueueBind(_queueName, _exchange, "");
            _consumer = new EventingBasicConsumer(_channel);
            _consumer.Received += (model, ea) =>
            {
                OnRecieve(ea.Body.ToArray());
            };
            _channel.BasicConsume(_queueName, true, _consumer);
            _sendTocken = new CancellationTokenSource();
            _send = Task.Run(() =>
            {
                try
                {
                    while (true)
                    {
                        while (_queue.TryDequeue(out var data))
                        {
                            _channel.BasicPublish(_exchange, "", null, data);
                        }
                        Task.WaitAny(new Task[] { Task.Delay(100) }, _sendTocken.Token);
                        if (_sendTocken.IsCancellationRequested)
                            break;
                    }
                }
                catch (Exception)
                {

                }
            });
        }

        public void Stop()
        {
            _channel.Close();
            _connection.Close();
            if (_send != null)
            {
                _sendTocken.Cancel();
                _send.Wait();
                _send = null;
                _sendTocken = null;
            }
        }
        public void Send(byte[] data)
        {
            _queue.Enqueue(data);
        }
    }
}
