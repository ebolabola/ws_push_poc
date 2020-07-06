using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.WebSockets;
using System.Threading.Tasks;
using Common;
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
        PushQueueReciever _queueRiceReciever;
        public void ConfigureServices(IServiceCollection services)
        {
            var instanceId = Guid.NewGuid();
            var connectionString = "amqp://guest:guest@127.0.0.1:5672";
            var logger = new Logger();
            var connectionManager = new ConnectionManager(instanceId, connectionString, logger);
            connectionManager.Start();
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
