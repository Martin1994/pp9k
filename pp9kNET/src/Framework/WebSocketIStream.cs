using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Net.WebSockets;
using System.Threading;
using System.Threading.Tasks;

namespace MartinCl2.IO
{
    public sealed class WebSocketIStream : Stream
    {
        private readonly WebSocket _websocket;
        private WebSocketMessageType _messageType = WebSocketMessageType.Close;
        private bool _end = false;

        public WebSocketIStream(WebSocket websocket)
        {
            if (websocket == null)
            {
                throw new ArgumentNullException("websocket");
            }
            _websocket = websocket;
        }

        public WebSocketMessageType MessageType
        {
            get
            {
                if (_messageType == WebSocketMessageType.Close)
                {
                    throw new InvalidOperationException("Message hasn't been received.");
                } else
                {
                    return _messageType;
                }
            }
        }

        public override bool CanRead
        {
            get
            {
                return true;
            }
        }

        public override bool CanSeek
        {
            get
            {
                return false;
            }
        }

        public override bool CanWrite
        {
            get
            {
                return false;
            }
        }

        public override long Length
        {
            get
            {
                throw new NotSupportedException();
            }
        }

        public override long Position
        {
            get
            {
                throw new NotSupportedException();
            }

            set
            {
                throw new NotSupportedException();
            }
        }

        public override void Flush()
        {
        }

        public override int Read(byte[] buffer, int offset, int count)
        {
            throw new NotSupportedException();
        }

        public override async Task<int> ReadAsync(byte[] buffer, int offset, int count, CancellationToken cancellationToken)
        {
            if (_end)
            {
                return 0;
            }
            ArraySegment<byte> wrapperedBuffer = new ArraySegment<byte>(buffer, offset, count);
            WebSocketReceiveResult result = await _websocket.ReceiveAsync(wrapperedBuffer, cancellationToken);
            if (_messageType == WebSocketMessageType.Close)
            {
                _messageType = result.MessageType;
            }
            if (result.EndOfMessage)
            {
                _end = true;
            }
            return result.Count;
        }

        public override long Seek(long offset, SeekOrigin origin)
        {
            throw new NotSupportedException();
        }

        public override void SetLength(long value)
        {
            throw new NotSupportedException();
        }

        public override void Write(byte[] buffer, int offset, int count)
        {
            throw new NotSupportedException();
        }
    }
}
