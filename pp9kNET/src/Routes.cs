using Microsoft.AspNetCore.Builder;
using Microsoft.AspNetCore.Routing;
using pp9kNET.Framework;
using pp9kNET.Handlers;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace pp9kNET
{
    public static class RoutesExtension
    {
        public static void RoutePp9k(this RouteBuilder builder, IApplicationBuilder app)
        {
            builder.Route<GameHandler>(app, "game");
            builder.Route<GameHandler>(app, "game/{gameid}");
        }
    }
}
