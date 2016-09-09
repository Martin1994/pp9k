using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Builder;
using Microsoft.AspNetCore.Hosting;
using Microsoft.AspNetCore.Http;
using Microsoft.Extensions.DependencyInjection;
using Microsoft.AspNetCore.Routing;
using Microsoft.Extensions.Logging;
using System.IO;
using Microsoft.Extensions.FileProviders;
using pp9kNET.Application;
using pp9kNET.Framework;

namespace pp9kNET
{
    public class Startup
    {
        // For more information on how to configure your application, visit http://go.microsoft.com/fwlink/?LinkID=398940
        public void ConfigureServices(IServiceCollection services)
        {
            services.AddRouting();
            services.AddSingleton(new Pp9kApplication());
        }

        public void Configure(IApplicationBuilder app, IHostingEnvironment env, ILoggerFactory loggerFactory)
        {
            loggerFactory.AddConsole();

            if (env.IsDevelopment())
            {
                app.UseDeveloperExceptionPage();
            }

            app.UseDefaultFiles();

            app.UseStaticFiles(new StaticFileOptions()
            {
                FileProvider = new PhysicalFileProvider(
                    Path.Combine(Directory.GetCurrentDirectory(), @"wwwroot")),
                RequestPath = new PathString("")
            });

            app.UseWebSockets();

            RouteBuilder routeBuilder = new RouteBuilder(app);
            routeBuilder.RoutePp9k(app);
            app.UseRouter(routeBuilder.Build());

            app.Run(async ctx =>
            {
                //HttpHandler handler = new HttpHandler();
                //await handler.CodeRespond(ctx, 404);
                ctx.Response.StatusCode = 404;
                await ctx.Response.WriteAsync(ctx.Request.Path + " not found.");
            });
        }
    }
}
