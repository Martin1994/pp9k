using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNet.Http;

namespace pp9kNET.Handlers
{
    public class ErrorHandler : IHttpHandler
    {
        protected Application _app;
        protected int _code;

        public ErrorHandler(int code)
        {
            _code = code;
        }

        public async Task Respond(HttpContext context)
        {
            context.Response.StatusCode = _code;
            await context.Response.WriteAsync(String.Format("Error {0}\n", _code.ToString()));
        }

        public static HandlerCreater Create(int code)
        {
            return (Application app) =>
            {
                ErrorHandler handler = new ErrorHandler(code);
                handler._app = app;
                return handler;
            };
        }
    }
}
