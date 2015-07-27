using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNet.Http;

using pp9kNET;
using System.Text.RegularExpressions;
using System.IO;

namespace pp9kNET.Handlers
{
    public class StaticHandler : IHttpHandler
    {
        protected Application _app;
        protected string _request_regex_pattern;
        protected string _file_directory;

        public StaticHandler(string pattern, string directory)
        {
            _request_regex_pattern = pattern;
            _file_directory = directory;
        }

        public async Task Respond(HttpContext context)
        {
            Match match = new Regex(_request_regex_pattern).Match(context.Request.Path);

            int length = match.Groups.Count;
            if (length < 2)
                length = 2;
            string[] matches = new string[length];
            matches[1] = "";
            for (int i = 0; i < match.Groups.Count; i++)
            {
                matches[i] = match.Groups[i].Value;
            }
            string file_path = String.Format(_file_directory, matches);

            if (!File.Exists(file_path))
            {
                IHttpHandler error_handler = new ErrorHandler(404);
                await error_handler.Respond(context);
                return;
            }
            
            await context.Response.SendFile(file_path);
        }
        
        public static HandlerCreater Create(string pattern, string directory)
        {
            return (Application app) =>
            {
                StaticHandler handler = new StaticHandler(pattern, directory);
                handler._app = app;
                return handler;
            };
        }
    }
}
