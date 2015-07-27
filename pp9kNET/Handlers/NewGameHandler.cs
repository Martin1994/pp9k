using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNet.Http;

namespace pp9kNET.Handlers
{
    public class NewGameHandler : IHttpHandler
    {
        protected Application _app;

        public async Task Respond(HttpContext context)
        {
            context.Response.ContentType = "application/json";
            
        }

        public static IHttpHandler Create(Application app)
        {
            NewGameHandler handler = new NewGameHandler();
            handler._app = app;
            return handler;
        }
    }
}
