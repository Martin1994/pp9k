using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Http;
using System.Reflection;
using System.Collections.ObjectModel;
using System.IO;

namespace pp9kNET.Framework
{
    public class HttpHandler : IHttpHandler
    {
        private HashSet<string> _allowedMethodsSet = null;
        private string _allowedMethods = null;
        
        private HashSet<string> AllowedMethodsSet
        {
            get
            {
                if (_allowedMethodsSet == null)
                {
                    _allowedMethodsSet = new HashSet<string>();
                    System.Type thisType = GetType();
                    System.Type baseType = typeof(HttpContext);
                    Action<string> checkAndAddMethod = (string method) =>
                    {
                        if (thisType.GetMethod(method, BindingFlags.Instance | BindingFlags.NonPublic).DeclaringType != baseType)
                        {
                            _allowedMethodsSet.Add(method.ToUpper());
                        }
                    };
                    checkAndAddMethod("Connect");
                    checkAndAddMethod("Delete");
                    checkAndAddMethod("Get");
                    checkAndAddMethod("Head");
                    _allowedMethodsSet.Add("OPTIONS");
                    checkAndAddMethod("Post");
                    checkAndAddMethod("Put");
                    _allowedMethodsSet.Add("TRACE");
                }
                return _allowedMethodsSet;
            }
        }

        protected string AllowedMethods
        {
            get
            {
                if (_allowedMethods == null)
                {
                    List<string> sortedMethods = AllowedMethodsSet.ToList();
                    sortedMethods.Sort();
                    _allowedMethods = string.Join(", ", sortedMethods);
                }
                return _allowedMethods;
            }
        }

        protected virtual async Task Connect(HttpContext context)
        {
            await CodeRespond(context, 405);
        }

        protected virtual async Task CustomMethod(HttpContext context)
        {
            await CodeRespond(context, 405);
        }

        protected virtual Task Delete(HttpContext context)
        {
            return CodeRespond(context, 405);
        }

        protected virtual Task Get(HttpContext context)
        {
            return CodeRespond(context, 405);
        }

        protected virtual Task Head(HttpContext context, string method)
        {
            return Task.FromResult(0);
        }

        protected Task Options(HttpContext context)
        {
            context.Response.StatusCode = 200;
            context.Response.Headers.Add("Allow", AllowedMethods);
            return Task.FromResult(0);
        }

        protected virtual Task Post(HttpContext context)
        {
            return CodeRespond(context, 405);
        }

        protected virtual Task Put(HttpContext context)
        {
            return CodeRespond(context, 405);
        }

        protected async Task Trace(HttpContext context)
        {
            context.Response.ContentType = "message/http";
            await context.Request.Body.CopyToAsync(context.Response.Body);
        }

        private static readonly Dictionary<int, string> _codeMessage = new Dictionary<int, string>()
        {
            #region Status Code Message
            { 100, "Continue" },
            { 101, "Switching Protocols" },
            { 200, "OK" },
            { 201, "Created" },
            { 202, "Accepted" },
            { 203, "Non-Authoritative Information" },
            { 204, "No Content" },
            { 205, "Reset Content" },
            { 206, "Partial Content" },
            { 207, "Multi-Status" },
            { 208, "Already Reported" },
            { 226, "IM Used" },
            { 300, "Multiple Choices" },
            { 301, "Moved Permanently" },
            { 302, "Found" },
            { 303, "See Other" },
            { 304, "Not Modified" },
            { 305, "Use Proxy" },
            { 306, "Switch Proxy" },
            { 307, "Temporary Redirect" },
            { 308, "Permanent Redirect" },
            { 400, "Bad Request" },
            { 401, "Unauthorized" },
            { 402, "Payment Required" },
            { 403, "Forbidden" },
            { 404, "Not Found" },
            { 405, "Method Not Allowed" },
            { 406, "Not Acceptable" },
            { 407, "Proxy Authentication Required" },
            { 408, "Request Timeout" },
            { 409, "Conflict" },
            { 410, "Gone" },
            { 411, "Length Required" },
            { 412, "Precondition Failed" },
            { 413, "Payload Too Large" },
            { 414, "URI Too Long" },
            { 415, "Unsupported Media Type" },
            { 416, "Range Not Satisfiable" },
            { 417, "Expectation Failed" },
            { 418, "I'm a teapot" },
            { 421, "Misdirected Request" },
            { 422, "Unprocessable Entity" },
            { 423, "Locked" },
            { 424, "Failed Dependency" },
            { 426, "Upgrade Required" },
            { 428, "Precondition Required" },
            { 429, "Too Many Requests" },
            { 431, "Request Header Fields Too Large" },
            { 451, "Unavailable For Legal Reasons" },
            { 500, "Internal Server Error" },
            { 501, "Not Implemented" },
            { 502, "Bad Gateway" },
            { 503, "Service Unavailable" },
            { 504, "Gateway Timeout" },
            { 505, "HTTP Version Not Supported" },
            { 506, "Variant Also Negotiates" },
            { 507, "Insufficient Storage" },
            { 508, "Loop Detected" },
            { 510, "Not Extended" },
            { 511, "Network Authentication Required" }
            #endregion
        };

        public virtual async Task CodeRespond(HttpContext context, int statusCode, bool withMessage = true)
        {
            context.Response.StatusCode = statusCode;
            if (withMessage)
            {
                string message;
                if (_codeMessage.TryGetValue(statusCode, out message))
                {
                    await context.Response.WriteAsync(message);
                }
            }
        }

        async Task IHttpHandler.Connect(HttpContext context)
        {
            if (AllowedMethodsSet.Contains("CONNECT"))
            {
                await Head(context, "CONNECT");
            }
            await Connect(context);
        }

        Task IHttpHandler.CustomMethod(HttpContext context)
        {
            return CustomMethod(context);
        }

        async Task IHttpHandler.Delete(HttpContext context)
        {
            if (AllowedMethodsSet.Contains("DELETE"))
            {
                await Head(context, "DELETE");
            }
            await Delete(context);
        }

        async Task IHttpHandler.Get(HttpContext context)
        {
            if (AllowedMethodsSet.Contains("GET"))
            {
                await Head(context, "GET");
            }
            await Get(context);
        }

        async Task IHttpHandler.Head(HttpContext context)
        {
            if (AllowedMethodsSet.Contains("HEAD"))
            {
                await Head(context, "GET");
            }
        }

        Task IHttpHandler.Options(HttpContext context)
        {
            return Options(context);
        }

        async Task IHttpHandler.Post(HttpContext context)
        {
            if (AllowedMethodsSet.Contains("POST"))
            {
                await Head(context, "POST");
            }
            await Post(context);
        }

        async Task IHttpHandler.Put(HttpContext context)
        {
            if (AllowedMethodsSet.Contains("PUT"))
            {
                await Head(context, "PUT");
            }
            await Put(context);
        }

        async Task IHttpHandler.Trace(HttpContext context)
        {
            if (AllowedMethodsSet.Contains("TRACE"))
            {
                await Head(context, "TRACE");
            }
            await Trace(context);
        }
    }
}
