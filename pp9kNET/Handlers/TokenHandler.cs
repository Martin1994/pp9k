using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNet.Http;

namespace pp9kNET.Handlers
{
    public class TokenHandler : IHttpHandler
    {
        protected Application _app;

        public async Task Respond(HttpContext context)
        {
            context.Response.ContentType = "application/json";

            if (!context.Request.Form.ContainsKey("gameid"))
            {
                await context.Response.WriteAsync("{\"success\": false, \"error\": \"gameid cannot be null.\"}");
                return;
            }

            Chloropp9kNET pp9k = _app.GetGame(context.Request.Form["gameid"]);

            if (!(pp9k is ChloroCometGame))
            {
                await context.Response.WriteAsync("{\"success\": true, \"token\": \"\"}");
                return;
            }

            await context.Response.WriteAsync("{\"success\": true, \"token\": \"" + ((ChloroCometGame)pp9k).Token + "\"}");
        }

        public static IHttpHandler Create(Application app)
        {
            TokenHandler handler = new TokenHandler();
            handler._app = app;
            return handler;
        }
    }
}
