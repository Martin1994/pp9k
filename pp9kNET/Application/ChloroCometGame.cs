using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Http;
using System.Threading.Tasks;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;

namespace pp9kNET
{
    public class ChloroCometGame : PassiveGame
    {
        public string Token { get { return _token; } }
        protected readonly string _token;

        public ChloroCometGame(string id) : base(id)
        {
            using (var client = new HttpClient())
            {
                Dictionary<string, string> values = new Dictionary<string, string>
                {
                    { "id", "pp9k" },
                    { "pass", "260ed07447b1dc102f0f0b2be073b468e4174ddb" },
                    { "client_id", _id }
                };

                FormUrlEncodedContent content = new FormUrlEncodedContent(values);

                HttpResponseMessage response = client.PostAsync("http://127.0.0.1:86/api/addClient", content).Result;
                
                string responseString = response.Content.ReadAsStringAsync().Result;

                JObject responseJson = JObject.Parse(responseString);

                JToken jtoken;
                if (!responseJson.TryGetValue("token", out jtoken))
                    throw new Exception("Failed to get comet token.");

                String token = jtoken.Value<string>();

                _token = token;
            };

            BoardChanged += OnBoardChangedComet;
            TurnChanged += OnTurnChangedComet;
        }

        ~ChloroCometGame()
        {
            using (var client = new HttpClient())
            {
                Dictionary<string, string> values = new Dictionary<string, string>
                {
                    { "hostid", "pp9k" },
                    { "hostpass", "260ed07447b1dc102f0f0b2be073b468e4174ddb" },
                    { "client_id", _id }
                };

                FormUrlEncodedContent content = new FormUrlEncodedContent(values);

                HttpResponseMessage response = client.PostAsync("http://127.0.0.1:86/api/removeClient", content).Result;

                string responseString = response.Content.ReadAsStringAsync().Result;

                JObject responseJson = JObject.Parse(responseString);

                JToken jtoken;
                if (!responseJson.TryGetValue("success", out jtoken) || !jtoken.Value<bool>())
                    throw new Exception("Failed to release comet token.");
            };
        }

        protected async void OnBoardChangedComet(int x, int y, Type type, Color side)
        {
            await SendMessage(
                "{\"success\": true, \"actions\": [" +
                    "{\"action\": \"update-board\", \"param\":" +
                        String.Format("[{{\"type\": \"{0}\", \"side\": \"{1}\", \"x\": {2}, \"y\": {3}}}]", type.ToString(), side.ToString(), x, y) +
                    "}" +
                "]}");
        }

        protected async void OnTurnChangedComet(Color side)
        {
            await SendMessage(
                "{\"success\": true, \"actions\": [" +
                    "{\"action\": \"update-turn\", \"param\": \"" + side.ToString() + "\"}" +
                "]}");
        }

        protected async Task SendMessage(string message)
        {
            using (var client = new HttpClient())
            {
                Dictionary<string, string> values = new Dictionary<string, string>
                {
                    { "id", "pp9k" },
                    { "pass", "260ed07447b1dc102f0f0b2be073b468e4174ddb" },
                    { "client_id", _id },
                    { "message", message }
                };

                FormUrlEncodedContent content = new FormUrlEncodedContent(values);

                HttpResponseMessage response = await client.PostAsync("http://127.0.0.1:86/api/send", content);

                string responseString = await response.Content.ReadAsStringAsync();

                JObject responseJson = JObject.Parse(responseString);

                JToken jtoken;
                if (!responseJson.TryGetValue("success", out jtoken) || !jtoken.Value<bool>())
                    throw new Exception("Failed to send message.");
            };
        }
    }
}
