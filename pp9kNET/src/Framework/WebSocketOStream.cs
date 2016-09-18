using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Net.WebSockets;
using System.Threading;
using System.Threading.Tasks;

namespace MartinCl2.IO
{
    public sealed class WebSocketOStream : Stream
    {
        private readonly WebSocket _websocket;
        private WebSocketMessageType _messageType = WebSocketMessageType.Text;
        private byte[] _pendingBuffer = new byte[0];
        private ArraySegment<byte> _pendingBytes = new ArraySegment<byte>(new byte[0], 0, 0);

        public WebSocketOStream(WebSocket websocket, WebSocketMessageType messageType)
        {
            if (websocket == null)
            {
                throw new ArgumentNullException("websocket");
            }
            _websocket = websocket;
            _messageType = messageType;
        }

        public override bool CanRead
        {
            get
            {
                return false;
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
                return true;
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
            throw new NotSupportedException();
        }

        public override async Task FlushAsync(CancellationToken cancellationToken)
        {
            if (_pendingBytes.Count > 0)
            {
                await _websocket.SendAsync(_pendingBytes, _messageType, true, cancellationToken);
            }
            _pendingBytes = new ArraySegment<byte>(new byte[0], 0, 0);
        }

        public override int Read(byte[] buffer, int offset, int count)
        {
            throw new NotSupportedException();
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

        public override async Task WriteAsync(byte[] buffer, int offset, int count, CancellationToken cancellationToken)
        {
            if(_pendingBytes.Count > 0)
            {
                bool endOfMessage = count == 0;
                await _websocket.SendAsync(_pendingBytes, _messageType, endOfMessage, cancellationToken);
            }
            if (_pendingBuffer.Length < buffer.Length)
            {
                _pendingBuffer = new byte[buffer.Length];
            }
            buffer.CopyTo(_pendingBuffer, offset);
            _pendingBytes = new ArraySegment<byte>(_pendingBuffer, 0, count);
        }
    }
}
