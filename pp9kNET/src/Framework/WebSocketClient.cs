using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Net.WebSockets;
using System.Threading;
using System.Threading.Tasks;

namespace MartinCl2.IO
{
    public class WebSocketClient
    {
        private readonly WebSocket _ws;
        private readonly SemaphoreSlim _writeLock = new SemaphoreSlim(1);

        public class WebSocketMessageEventArgs : EventArgs
        {
            private readonly string _message;
            public string Message { get { return _message; } }

            public WebSocketMessageEventArgs(string message)
            {
                _message = message;
            }
        }

        public delegate Task WebSocketMessageHandler(WebSocketMessageEventArgs args);

        public event WebSocketMessageHandler OnMessage;

        public event Func<Task> OnClose;

        public WebSocketClient(WebSocket ws)
        {
            _ws = ws;
        }

        public async Task Send(string message)
        {
            await _writeLock.WaitAsync();
            try
            {
                WebSocketOStream ostream = new WebSocketOStream(_ws, WebSocketMessageType.Text);
                StreamWriter writer = new StreamWriter(ostream);
                await writer.WriteAsync(message);
                await writer.FlushAsync();
            }
            finally
            {
                _writeLock.Release();
            }
        }

        public async Task Listen()
        {
            while (_ws.State == WebSocketState.Open)
            {
                WebSocketIStream istream = new WebSocketIStream(_ws);
                StreamReader reader = new StreamReader(istream);
                string message = await reader.ReadToEndAsync();
                OnMessage?.Invoke(new WebSocketMessageEventArgs(message));
            }
            OnClose?.Invoke();
        }

        public async Task Close(string reason)
        {
            await _ws.CloseAsync(WebSocketCloseStatus.NormalClosure, reason, CancellationToken.None);
        }
    }
}
