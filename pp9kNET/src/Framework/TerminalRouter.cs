using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Routing;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace pp9kNET.Framework
{
    public class TerminalRouter<T> : IRouter where T : IHttpHandler, new()
    {
        public TerminalRouter()
        {
        }

        public VirtualPathData GetVirtualPath(VirtualPathContext context)
        {
            return null;
        }

        public Task RouteAsync(RouteContext context)
        {
            T handler = new T();
            switch(context.HttpContext.Request.Method)
            {
                case "CONNECT":
                    context.Handler = handler.Connect;
                    break;

                case "DELETE":
                    context.Handler = handler.Delete;
                    break;

                case "GET":
                    context.Handler = handler.Get;
                    break;

                case "HEAD":
                    context.Handler = handler.Head;
                    break;

                case "OPTIONS":
                    context.Handler = handler.Options;
                    break;

                case "POST":
                    context.Handler = handler.Post;
                    break;

                case "PUT":
                    context.Handler = handler.Put;
                    break;

                case "TRACE":
                    context.Handler = handler.Trace;
                    break;

                default:
                    context.Handler = handler.CustomMethod;
                    break;
            }

            return Task.FromResult(0);
        }
    }
}
