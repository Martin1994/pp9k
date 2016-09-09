using Microsoft.AspNetCore.Http;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace pp9kNET.Framework
{
    public interface IHttpHandler
    {
        Task Connect(HttpContext context);

        Task CustomMethod(HttpContext context);

        Task Delete(HttpContext context);

        Task Get(HttpContext context);

        Task Head(HttpContext context);

        Task Options(HttpContext context);

        Task Post(HttpContext context);

        Task Put(HttpContext context);

        Task Trace(HttpContext context);
    }
}
