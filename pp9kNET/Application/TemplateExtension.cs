using Microsoft.AspNet.Http;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Threading.Tasks;

namespace pp9kNET
{
    public static class TemplateExtension
    {
        public static async Task SendFile(this HttpResponse response, string path)
        {
            if (response.SupportsSendFile())
            {
                await response.SendFileAsync(path);
            }
            else
            {
                string content = File.ReadAllText(path);
                await response.WriteAsync(content);
            }
        }

        public static async Task RenderTemplate(this HttpResponse response, string template, params string[] args)
        {
            string path = "./Templates/" + template + ".html";
            if (args.Length == 0)
            {
                await response.SendFile(path);
            }
            else
            {
                string content = String.Format(File.ReadAllText(path), args);
                await response.WriteAsync(content);
            }
        }
    }
}
