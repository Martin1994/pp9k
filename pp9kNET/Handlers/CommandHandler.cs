using Microsoft.AspNet.Http;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text.RegularExpressions;
using System.Threading.Tasks;

namespace pp9kNET.Handlers
{
    public class CommandHandler : IHttpHandler
    {
        protected Application _app;
        protected string _request_regex_pattern;

        public CommandHandler(string pattern)
        {
            _request_regex_pattern = pattern;
        }

        public async Task Respond(HttpContext context)
        {
            context.Response.ContentType = "application/json";

            // Load game object
            if (context.Request.ContentType == null || !context.Request.Form.ContainsKey("gameid"))
            {
                await ErrorMessage(context, "Please specify game ID.");
                return;
            }

            string gameid = context.Request.Form["gameid"];
            PassiveGame pp9k = (PassiveGame)_app.GetGame(gameid);

            if (pp9k == null)
            {
                await ErrorMessage(context, "Invalid game ID \\\"" + gameid + "\\\".");
                return;
            }

            // Get command
            Match match = new Regex(_request_regex_pattern).Match(context.Request.Path);

            if (match.Groups.Count < 2)
            {
                await ErrorMessage(context, "Please specify command.");
                return;
            }

            string command = match.Groups[1].Value;

            List<string> actions;

            // Process command
            switch (command)
            {
                case "refresh":
                    actions = new List<string>()
                    {
                        "{\"action\": \"update-board\", \"param\": [" + pp9k.BoardJson + "]}",
                        "{\"action\": \"update-turn\", \"param\": \"" + pp9k.Turn.ToString() + "\"}"
                    };
                    await context.Response.WriteAsync(SuccessJson(actions));
                    return;

                case "move":
                    if (   !context.Request.Form.ContainsKey("from-x")
                        || !context.Request.Form.ContainsKey("from-y")
                        || !context.Request.Form.ContainsKey("to-x")
                        || !context.Request.Form.ContainsKey("to-y"))
                    {
                        await ErrorMessage(context, "Please specify move position.");
                        return;
                    }

                    int from_x;
                    int from_y;
                    int to_x;
                    int to_y;
                    if (   !Int32.TryParse(context.Request.Form["from-x"], out from_x)
                        || !Int32.TryParse(context.Request.Form["from-y"], out from_y)
                        || !Int32.TryParse(context.Request.Form["to-x"], out to_x)
                        || !Int32.TryParse(context.Request.Form["to-y"], out to_y))
                    {
                        await ErrorMessage(context, String.Format("Invalid move position ({0}, {1}) -> ({2}, {3}).",
                                                                  context.Request.Form["from-x"],
                                                                  context.Request.Form["from-y"],
                                                                  context.Request.Form["to-x"],
                                                                  context.Request.Form["to-y"]));
                        return;
                    }

                    if (!pp9k.MakeMove(from_x, from_y, to_x, to_y))
                    {
                        return;
                    }
                    /*
                    actions = new List<string>()
                    {
                        "{\"action\": \"update-board\", \"param\": [" + pp9k.BoardJson + "]}",
                        "{\"action\": \"update-turn\", \"param\": \"" + pp9k.Turn.ToString() + "\"}"
                    };
                    await context.Response.WriteAsync(SuccessJson(actions));
                    */
                    return;

                default:
                    await ErrorMessage(context, "Invalid command \\\"" + command + "\\\".");
                    return;
            }
        }

        public async Task ErrorMessage(HttpContext context, string message)
        {
            await context.Response.WriteAsync("{\"success\": false, \"error\": \"" + message + "\"}");
        }

        public string SuccessJson(List<string> actions)
        {
            return "{\"success\": true, \"actions\": [" + String.Join(", ", actions) + "]}";
        }

        public static HandlerCreater Create(string pattern)
        {
            return (Application app) =>
            {
                CommandHandler handler = new CommandHandler(pattern);
                handler._app = app;
                return handler;
            };
        }
    }
}
