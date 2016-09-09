using Microsoft.AspNetCore.Builder;
using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Routing;
using Microsoft.Extensions.DependencyInjection;

namespace pp9kNET.Framework
{
    public static class RoutingExtension
    {
        public static void Route<T>(this RouteBuilder builder, IApplicationBuilder app, string pattern) where T:IHttpHandler, new()
        {
            builder.Routes.Add(new Route(new TerminalRouter<T>(), pattern, app.ApplicationServices.GetService<IInlineConstraintResolver>()));
        }
    }
}
