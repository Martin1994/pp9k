using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Http;
using Microsoft.Extensions.DependencyInjection;
using pp9kNET.Application;
using pp9kNET.Framework;

namespace pp9kNET.Handlers
{
    public class Pp9kHandler : HttpHandler
    {
        protected Pp9kApplication _app = null;

        protected override Task Head(HttpContext context, string method)
        {
            context.Response.ContentType = "application/json; charset=utf-8";
            return Task.FromResult(0);
        }

        protected Pp9kApplication GetApp(HttpContext context)
        {
            return context.RequestServices.GetRequiredService<Pp9kApplication>();
        }
    }
}
