using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Http;
using Microsoft.Extensions.Primitives;
using Newtonsoft.Json.Linq;
using pp9kNET.Application;
using pp9kNET.Framework;
using MartinCl2.IO;
using System.Net.WebSockets;
using Microsoft.AspNetCore.Routing;
using Newtonsoft.Json;

namespace pp9kNET.Handlers
{
    public class GameHandler : Pp9kHandler
    {
        /// <summary>
        /// Get the game info of a game
        /// </summary>
        /// <param name="context"></param>
        /// <returns></returns>
        protected override async Task Get(HttpContext context)
        {
            _app = GetApp(context);

            string gameid = (string)context.GetRouteValue("gameid");
            if (gameid == null)
            {
                IEnumerable<Pp9kGame> games = _app.Games;
                JArray allDescriptions = new JArray();
                foreach(Pp9kGame game in games.ToArray())
                {
                    allDescriptions.Add(game.Description);
                }
                await context.Response.WriteJsonAsync(allDescriptions);
            }
            else
            {

                Pp9kGame game = _app.GetGame(gameid);
                if (game == null)
                {
                    context.Response.StatusCode = 400;
                    await context.Response.WriteJsonAsync(new JObject()
                    {
                        { "message", "Game doesn't exist." },
                        { "gameid", gameid }
                    });
                    return;
                }
                
                if (context.WebSockets.IsWebSocketRequest)
                {
                    WebSocket ws = await context.WebSockets.AcceptWebSocketAsync();
                    WebSocketClient client = new WebSocketClient(ws);
                    client.OnMessage += async (args) =>
                    {
                        JObject operation;
                        try
                        {
                            operation = JObject.Parse(args.Message);
                        }
                        catch
                        {
                            await client.Send(new JObject()
                            {
                                { "error", "Invalid JSON." }
                            }.ToString(Formatting.None));
                            return;
                        }
                        JObject result;
                        try
                        {
                            result = game.Operate(operation, client);
                        }
                        catch (Exception)
                        {
                            result = new JObject()
                            {
                                { "error", "Internal server error." }
                            };
                        }
                        await client.Send(result.ToString(Formatting.None));
                    };
                    game.AddClient(client);
                    await client.Listen();
                }
                else
                {
                    await context.Response.WriteJsonAsync(game.Description);
                }
            }
        }

        /// <summary>
        /// Create a new game
        /// </summary>
        /// <param name="context">
        /// Input:
        /// black - type of black player
        /// name - name of the game
        /// password - password of the game
        /// white - type of white player
        /// 
        /// Output:
        /// Game description. See Pp9kGame.
        /// </param>
        /// <returns></returns>
        protected override async Task Post(HttpContext context)
        {
            _app = GetApp(context);

            if (!context.Request.HasFormContentType)
            {
                context.Response.StatusCode = 400;
                await context.Response.WriteJsonAsync(new JObject()
                    {
                        { "message", "Invalid content type" },
                        { "type", context.Request.ContentType }
                    });
                return;
            }

            // Get player type
            StringValues whiteStr;
            Player white;
            if (context.Request.Form.TryGetValue("white", out whiteStr))
            {
                if (!TryToPlayer(whiteStr, out white))
                {
                    context.Response.StatusCode = 400;
                    await context.Response.WriteJsonAsync(new JObject()
                    {
                        { "message", "Invalid white player type." },
                        { "type", (string)whiteStr }
                    });
                    return;
                }
            }
            else
            {
                white = Player.Human;
            }
            StringValues blackStr;
            Player black;
            if (context.Request.Form.TryGetValue("black", out blackStr))
            {
                if (!TryToPlayer(blackStr, out black))
                {
                    context.Response.StatusCode = 400;
                    await context.Response.WriteJsonAsync(new JObject()
                    {
                        { "message", "Invalid black player type." },
                        { "type", (string)blackStr }
                    });
                    return;
                }
            }
            else
            {
                black = Player.Human;
            }

            // Get password
            string password;
            StringValues passwordValue;
            if (context.Request.Form.TryGetValue("password", out passwordValue))
            {
                password = passwordValue;
            }
            else
            {
                password = null;
            }
            // TODO: set password

            // Create Game
            Pp9kGame game;
            try
            {
                game = _app.CreateGame(black, white, password);
            }
            catch (Exception)
            {
                context.Response.StatusCode = 500;
                await context.Response.WriteJsonAsync(new JObject()
                {
                    { "message", "Failed to create game." }
                });
                return;
            }

            // Get name
            string name;
            StringValues nameValue;
            if (context.Request.Form.TryGetValue("name", out nameValue) && nameValue != "")
            {
                name = nameValue;
            }
            else
            {
                name = "Game " + game.Id;
            }
            game.Name = name;

            await context.Response.WriteJsonAsync(game.Description);
        }

        protected override async Task Put(HttpContext context)
        {
            _app = GetApp(context);

            string gameid = (string)context.GetRouteValue("gameid");
            if (gameid == null)
            {
                context.Response.StatusCode = 400;
                await context.Response.WriteJsonAsync(new JObject()
                {
                    { "message", "Gameid must be specified." }
                });
                return;
            }

            Pp9kGame game = _app.GetGame(gameid);
            if (game == null)
            {
                context.Response.StatusCode = 400;
                await context.Response.WriteJsonAsync(new JObject()
                {
                    { "message", "Game doesn't exist." },
                    { "gameid", gameid }
                });
                return;
            }

            // Get password
            string password;
            StringValues passwordValue;
            if (context.Request.Form.TryGetValue("password", out passwordValue))
            {
                password = passwordValue;
            }
            else
            {
                password = null;
            }

            if (!game.CheckPassword(password))
            {
                context.Response.StatusCode = 401;
                await context.Response.WriteJsonAsync(new JObject()
                {
                    { "message", "Incorrect password." }
                });
                return;
            }

            // Get operation
            string operationStr;
            StringValues operationValue;
            if (context.Request.Form.TryGetValue("action", out operationValue))
            {
                operationStr = operationValue;
            }
            else
            {
                context.Response.StatusCode = 400;
                await context.Response.WriteJsonAsync(new JObject()
                {
                    { "message", "Operation is missing." }
                });
                return;
            }

            JObject operation;
            try
            {
                operation = JObject.Parse(operationStr);
            }
            catch
            {
                context.Response.StatusCode = 400;
                await context.Response.WriteJsonAsync(new JObject()
                {
                    { "message", "Invalid operation json data." }
                });
                return;
            }

            JObject result;
            try
            {
                result = game.Operate(operation, null);
            }
            catch (Exception)
            {
                await CodeRespond(context, 500);
                return;
            }

            JToken error;
            if (result.TryGetValue("error", out error))
            {
                context.Response.StatusCode = 400;
            }

            await context.Response.WriteJsonAsync(result);
        }

        private static bool TryToPlayer(string playerStr, out Player player)
        {
            switch (playerStr)
            {
                case "human":
                    player = Player.Human;
                    return true;

                case "computer1":
                    player = Player.AI1;
                    return true;

                case "computer2":
                    player = Player.AI2;
                    return true;

                case "computer3":
                    player = Player.AI3;
                    return true;

                case "computer4":
                    player = Player.AI4;
                    return true;

                default:
                    player = default(Player);
                    return false;
            }
        }
    }
}
