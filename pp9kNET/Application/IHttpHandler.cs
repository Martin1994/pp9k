using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNet.Builder;
using Microsoft.AspNet.Http;
using Microsoft.Framework.DependencyInjection;

namespace pp9kNET
{
    public interface IHttpHandler
    {
        Task Respond(HttpContext context);
    }
}
