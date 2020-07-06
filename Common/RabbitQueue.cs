using RabbitMQ.Client;
using RabbitMQ.Client.Events;
using System;
using System.Collections.Concurrent;
using System.Threading;
using System.Threading.Tasks;

namespace Backend.Common.EntitySync.RMQ
{
    public class RabbitQueue
    {
        private string _connectionString;
        private string _queueName;
        private string _key;
        private Action<byte[]> _onRecieve;
        private IConnection _connection;
        private IModel _channel;
        private EventingBasicConsumer _consumer;
        private ConcurrentQueue<byte[]> _queue = new ConcurrentQueue<byte[]>();
        private Task _send;
        private CancellationTokenSource _sendTocken;


        public static RabbitQueue CreateSender(string connection, string queueName, string partition)
        {
            return new RabbitQueue(connection, queueName, partition, null, "");
        }
        public static RabbitQueue CreateReciever(string connection, string queueName, string partition, Action<byte[]> onRecieve, string key = "")
        {
            return new RabbitQueue(connection, queueName, partition, onRecieve, key);
        }

        public RabbitQueue(string connection, string queueName, string partition, Action<byte[]> onRecieve, string key = "")
        {
            _connectionString = connection;
            _queueName = $"{queueName}_{partition}";
            _key = key;
            _onRecieve = onRecieve;

        }
        public void Send(byte[] data)
        {
            _queue.Enqueue(data);
        }
        public void Start()
        {
            var factory = new ConnectionFactory();
            factory.Uri = new Uri(_connectionString);
            _connection = factory.CreateConnection();
            _channel = _connection.CreateModel();
            _channel.ExchangeDeclare(_queueName, "direct");
            _channel.QueueDeclare(_queueName, true, false, false);
            if (_onRecieve != null)
            {
                _channel.QueueBind(_queueName, _queueName, _key);
                _consumer = new EventingBasicConsumer(_channel);
                _consumer.Received += (model, ea) =>
                {
                    var body = ea.Body;
                    _onRecieve(body.ToArray());
                };
                _channel.BasicConsume(_queueName, true, _consumer);
            }
            else
            {
                _sendTocken = new CancellationTokenSource();
                _send = Task.Run(() =>
                {
                    try
                    {
                        while (true)
                        {
                            while (_queue.TryDequeue(out var data))
                            {
                                _channel.BasicPublish(_queueName, "", null, data);
                            }
                            Task.WaitAny(new Task[] { Task.Delay(100) }, _sendTocken.Token);
                            if (_sendTocken.IsCancellationRequested)
                                break;
                        }
                    }
                    catch (Exception )
                    {

                    }
                });
            }

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
    }
}
