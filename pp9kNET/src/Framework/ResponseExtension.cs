using Microsoft.AspNetCore.Http;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Threading.Tasks;

namespace pp9kNET.Framework
{
    public static class ResponseExtension
    {
        private static JsonSerializer jsonSerializer = new JsonSerializer();
        public static async Task WriteJsonAsync(this HttpResponse response, JToken json)
        {
            //Stream stream = new ResponseStream(response);
            //TextWriter writer = new StreamWriter(stream);
            //jsonSerializer.Serialize(writer, json, typeof(JToken));
            //await writer.FlushAsync();
            string content = json.ToString(Formatting.None);
            await response.WriteAsync(content);
        }
    }
}
