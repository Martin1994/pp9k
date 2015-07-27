using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace pp9kNET
{
    public class PassiveGame : Chloropp9kNET
    {
        public const int BoardSize = 8;

        protected Piece[,] _pieces = new Piece[BoardSize, BoardSize];

        protected Color _turn;

        public Color Turn { get { return _turn; } }

        public PassiveGame() : base()
        {
            for (int i = 0; i < BoardSize; i++)
            {
                for (int j = 0; j < BoardSize; j++)
                {
                    _pieces[i, j] = new Piece(Type.Blank, Color.White);
                }
            }

            _turn = Color.White;

            BoardChanged += OnBoardChanged;
            TurnChanged += OnTurnChanged;
        }

        protected void OnBoardChanged(int x, int y, Type type, Color side)
        {
            _pieces[x, y] = new Piece(type, side);
        }

        protected void OnTurnChanged(Color side)
        {
            _turn = side;
        }

        public string BoardJson
        {
            get
            {
                List<string> piece_str = new List<string>(BoardSize * BoardSize);

                for (int i = 0; i < BoardSize; i++)
                {
                    for (int j = 0; j < BoardSize; j++)
                    {
                        Piece piece = _pieces[i, j];
                        piece_str.Add(String.Format("{{\"type\": \"{0}\", \"side\": \"{1}\", \"x\": {2}, \"y\": {3}}}", piece.Type.ToString(), piece.Side.ToString(), i, j));
                    }
                }

                return String.Join(", ", piece_str);
            }
        }
    }

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
