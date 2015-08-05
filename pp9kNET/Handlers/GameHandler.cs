using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNet.Http;

namespace pp9kNET.Handlers
{
    public class GameHandler : IHttpHandler
    {
        protected Application _app;

        public async Task Respond(HttpContext context)
        {
            context.Response.ContentType = "text/html";

            await context.Response.RenderTemplate("Header");
            await context.Response.RenderTemplate("Game");
            await context.Response.RenderTemplate("Footer");
        }

        public static IHttpHandler Create(Application app)
        {
            GameHandler handler = new GameHandler();
            handler._app = app;
            return handler;
        }
    }
}
