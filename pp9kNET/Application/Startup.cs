using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNet.Builder;
using Microsoft.AspNet.Http;
using Microsoft.Framework.DependencyInjection;

using pp9kNET.Handlers;
using System.Text.RegularExpressions;

namespace pp9kNET
{
    public delegate IHttpHandler HandlerCreater(Application app);

    public class Startup
    {
        // For more information on how to configure your application, visit http://go.microsoft.com/fwlink/?LinkID=398940
        public void ConfigureServices(IServiceCollection services)
        {
            
        }

        protected Dictionary<string, HandlerCreater> _handlers = new Dictionary<string, HandlerCreater>()
        {
            { "^/$" , WelcomeHandler.Create },
            { "^/newgame$" , NewGameHandler.Create },
            { "^/game$" , GameHandler.Create },
            { "^/static/(.*)$" , StaticHandler.Create("^/static/(.*)$", "./Static/{1}") },
            { "default" , ErrorHandler.Create(404) },
            { "exception" , ErrorHandler.Create(500) }
        };

        public void Configure(IApplicationBuilder app)
        {
            Application pp9k_app = new Application();

            app.Run(async (context) =>
            {
                IHttpHandler handler = null;

                foreach(KeyValuePair<string, HandlerCreater> kvp in _handlers)
                {
                    Regex regex = new Regex(kvp.Key);
                    HandlerCreater create_handler = kvp.Value;

                    if (regex.Match(context.Request.Path).Success)
                    {
                        handler = create_handler(pp9k_app);
                        break;
                    }
                }

                if (handler == null)
                    handler = _handlers["default"](pp9k_app);

                try
                {
                    await handler.Respond(context);
                }
                catch (Exception ex)
                {
                    await _handlers["exception"](pp9k_app).Respond(context);
                    await context.Response.WriteAsync(ex.Message + "\n" + ex.StackTrace + "\n");
                }
            });
        }
    }
}
