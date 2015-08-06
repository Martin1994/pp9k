using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace pp9kNET
{
    public class Piece
    {
        public Type Type { get { return _type; } }
        public Color Side { get { return _side; } }
        private Type _type;
        private Color _side;

        public Piece(Type type, Color side)
        {
            _type = type;
            _side = side;
        }
    }
}
