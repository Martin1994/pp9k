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
        protected Dictionary<string, string> _content_types;

        public StaticHandler(string pattern, string directory, Dictionary<string, string> content_types)
        {
            _request_regex_pattern = pattern;
            _file_directory = directory;
            _content_types = content_types;
        }

        public async Task Respond(HttpContext context)
        {
            // Get path
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
             
            // Check existance
            if (!File.Exists(file_path))
            {
                IHttpHandler error_handler = new ErrorHandler(404);
                await error_handler.Respond(context);
                return;
            }

            // Change content type if needed
            string ext = Path.GetExtension(file_path);
            if (_content_types.ContainsKey(ext))
            {
                context.Response.ContentType = _content_types[ext];
            }
            
            await context.Response.SendFile(file_path);
        }
        
        public static HandlerCreater Create(string pattern, string directory, Dictionary<string, string> content_types)
        {
            return (Application app) =>
            {
                StaticHandler handler = new StaticHandler(pattern, directory, content_types);
                handler._app = app;
                return handler;
            };
        }
    }
}
