using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.WebSockets;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Builder;
using Microsoft.AspNetCore.Hosting;
using Microsoft.AspNetCore.Http;
using Microsoft.Extensions.DependencyInjection;
using Microsoft.Extensions.Hosting;
using proto.PushService;

namespace PushService
{
    public class Startup
    {
        QueueRiceReciever _queueRiceReciever;
        public void ConfigureServices(IServiceCollection services)
        {
            var instanceId = Guid.NewGuid().GetHashCode();
            var connectionManager = new ConnectionManager(instanceId);
            _queueRiceReciever = new QueueRiceReciever("amqp://guest:guest@127.0.0.1:5672", instanceId, connectionManager, PushMessageType.PresenceService);
            services.AddSingleton<IConnectionManager>(connectionManager);
        }
        public void Configure(IApplicationBuilder app, IWebHostEnvironment env)
        {
            if (env.IsDevelopment())
            {
                app.UseDeveloperExceptionPage();
            }
            app.UseRouting();
            var webSocketOptions = new WebSocketOptions()
            {
                KeepAliveInterval = TimeSpan.FromSeconds(120),
                ReceiveBufferSize = 4 * 1024
            };

            app.UseWebSockets(webSocketOptions);
            app.UseMiddleware<PushMiddleware>();

        }
    }
}
