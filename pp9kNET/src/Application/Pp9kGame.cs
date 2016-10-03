using MartinCl2.IO;
using System;
using System.Collections.Generic;
using System.Collections.Concurrent;
using System.Linq;
using System.Net.WebSockets;
using System.Threading.Tasks;
using System.Threading;
using Newtonsoft.Json.Linq;

namespace pp9kNET.Application
{
    /// <summary>
    /// Game instance
    /// </summary>
    public class Pp9kGame : Chloropp9kNET
    {
        private string _password = null;

        private string _name = "";
        public string Name { get { return _name; } set { _name = value; } }

        private double _blackScore = 0;
        public double BlackScore { get { return _blackScore; } }
        private double _whiteScore = 0;
        public double WhiteScore { get { return _whiteScore; } }

        private readonly DateTime _createTime;
        public DateTime CreateTime { get { return _createTime; } }

        private readonly ConcurrentDictionary<WebSocketClient, bool> _clients = new ConcurrentDictionary<WebSocketClient, bool>();
        public IEnumerable<WebSocketClient> Clients { get { return _clients.Keys; } }

        private string _id = "";
        public string Id
        {
            get
            {
                return _id;
            }
            set
            {
                _id = value;
            }
        }
        public const int BoardSize = 8;

        protected Piece[,] _pieces = new Piece[BoardSize, BoardSize];
        public JArray BoardJson
        {
            get
            {
                JArray board = new JArray();
                for (int i = 0; i < BoardSize; i++)
                {
                    for (int j = 0; j < BoardSize; j++)
                    {
                        Piece piece = _pieces[i, j];
                        JObject pieceJson = new JObject() {
                            { "type", piece.Type.ToString() },
                            { "side", piece.Side.ToString() },
                            { "x", i },
                            { "y", j }
                        };
                        board.Add(pieceJson);
                    }
                }
                return board;
            }
        }

        protected Color _turn;

        public Color Turn { get { return _turn; } }

        public JToken Description
        {
            get
            {
                return new JObject()
                {
                    { "name", _name },
                    { "id", _id },
                    { "createTime", _createTime },
                    { "connectedClients", _clients.Count },
                    //{ "blackScore", _blackScore },
                    //{ "whiteScore", _whiteScore },
                    { "protected", CheckPassword("") }
                };
            }
        }

        public Pp9kGame() : base()
        {
            _createTime = DateTime.Now;

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
            ScoreShown += OnScoreShown;
            Won += OnWon;
            Drawn += OnDrawn;
        }

        private async void OnDrawn()
        { 
            await Boardcast(new JObject()
            {
                { "message", "Draw!" }
            });
        }

        private async void OnWon(Color side, bool checkmate)
        {
            await Boardcast(new JObject()
            {
                { "message", side.ToString() + " win!" }
            });
        }

        private async void OnBoardChanged(int x, int y, Type type, Color side)
        {
            _pieces[x, y] = new Piece(type, side);
            await Boardcast(new JObject()
            {
                { "update_board", new JArray()
                    {
                        new JObject()
                        {
                            { "type", type.ToString() },
                            { "side", side.ToString() },
                            { "x", x },
                            { "y", y }
                        }
                    }
                }
            });
        }

        private async void OnTurnChanged(Color side)
        {
            _turn = side;
            await Boardcast(new JObject()
            {
                { "update_turn", Turn.ToString() }
            });
        }

        private void OnScoreShown(double score1, double score2)
        {
            _blackScore = score2;
            _whiteScore = score1;
        }

        public bool CheckPassword(string toVerify)
        {
            return _password == null || toVerify == _password;
        }

        public void AddClient(WebSocketClient client)
        {
            bool verfied = CheckPassword(""); // If password is empty, get verfied automatically
            _clients.AddOrUpdate(client, verfied, (key, value) => verfied);
            client.OnClose += () =>
            {
                bool success;
                _clients.TryRemove(client, out success);
                return Task.FromResult(0);
            };
        }

        public async Task Boardcast(JObject message)
        {
            foreach (WebSocketClient client in Clients)
            {
                await client.Send(message.ToString(Newtonsoft.Json.Formatting.None));
            }
        }

        /// <summary>
        /// Disconnect all the clients and show ending informations
        /// </summary>
        /// <returns></returns>
        public async Task EndGame()
        {
            Exit();
            foreach (WebSocketClient client in Clients.ToList())
            {
                await client.Close("Game end.");
            }
        }

        /// <summary>
        /// A controller accepting json input
        /// </summary>
        /// <param name="operation"></param>
        /// <param name="client">The WebSocket client that request this operation. null means this operation is requested by RESTful api instead of WebSocket</param>
        /// <returns></returns>
        public JObject Operate(JObject operation, WebSocketClient client)
        {
            JToken actionToken;
            if (!operation.TryGetValue("action", out actionToken))
            {
                return new JObject()
                {
                    { "error", "Must specify \"action\"." }
                };
            }
            string action = actionToken.ToString();

            switch (action)
            {
                case "authorize":
                    if (client == null)
                    {
                        goto default;
                    }

                    JToken passwordToken;
                    if (!operation.TryGetValue("password", out passwordToken))
                    {
                        return new JObject()
                        {
                            { "error", "Must specify \"password\"." }
                        };
                    }
                    string password = passwordToken.ToString();
                    if (CheckPassword(password))
                    {
                        _clients.TryUpdate(client, true, false);
                        return new JObject()
                        {
                            { "message", "Authorized successfully." },
                            { "authorize", true }
                        };
                    }
                    else
                    {
                        return new JObject()
                        {
                            { "error", "Failed to authorize." }
                        };
                    }

                case "init":
                    return new JObject()
                    {
                        { "update_board", BoardJson },
                        { "update_turn", Turn.ToString() }
                    };

                case "move":
                    JToken from;
                    if (!operation.TryGetValue("from", out from) && from.Type == JTokenType.Object)
                    {
                        return new JObject()
                        {
                            { "error", "Must specify \"from\"." }
                        };
                    }
                    JToken to;
                    if (!operation.TryGetValue("to", out to) && to.Type == JTokenType.Object)
                    {
                        return new JObject()
                        {
                            { "error", "Must specify \"to\"." }
                        };
                    }
                    JToken fromX;
                    if (!((JObject)from).TryGetValue("x", out fromX))
                    {
                        return new JObject()
                        {
                            { "error", "Must specify \"from.x\"." }
                        };
                    }
                    JToken fromY;
                    if (!((JObject)from).TryGetValue("y", out fromY))
                    {
                        return new JObject()
                        {
                            { "error", "Must specify \"from.y\"." }
                        };
                    }
                    JToken toX;
                    if (!((JObject)to).TryGetValue("x", out toX))
                    {
                        return new JObject()
                        {
                            { "error", "Must specify \"to.x\"." }
                        };
                    }
                    JToken toY;
                    if (!((JObject)to).TryGetValue("y", out toY))
                    {
                        return new JObject()
                        {
                            { "error", "Must specify \"to.y\"." }
                        };
                    }
                    if(!MakeMove((int)fromX, (int)fromY, (int)toX, (int)toY))
                    {
                        return new JObject()
                        {
                            { "error", "Failed to move" }
                        };
                    }
                    return new JObject();

                default:
                    return new JObject()
                    {
                        { "error", "Unexpected action." }
                    };
            }
        }
    }
}
