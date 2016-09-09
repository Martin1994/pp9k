using System;
using System.Collections.Concurrent;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace pp9kNET.Application
{
    /// <summary>
    /// The application singleton managing all the game instances.
    /// </summary>
    public class Pp9kApplication
    {
        public IEnumerable<Pp9kGame> Games { get { return _games.Values; } }
        private readonly ConcurrentDictionary<string, Pp9kGame> _games = new ConcurrentDictionary<string, Pp9kGame>();

        private readonly Object _concurrentLock = new Object();
        
        private readonly Random _rnd = new Random();
        
        protected virtual int _idLength
        {
            get { return 6; }
        }

        /// <summary>
        /// Create a new game for the application
        /// </summary>
        /// <param name="player1">Type for the white player</param>
        /// <param name="player2">Type for the black player</param>
        /// <param name="password"></param>
        /// <returns>Game instance</returns>
        public Pp9kGame CreateGame(Player player1, Player player2, string password = null)
        {
            Pp9kGame game = new Pp9kGame();
            char[] gameid = new char[_idLength];
            string roomidStr;

            // Generate game id
            do
            {
                for (int i = 0; i < _idLength; i++)
                {
                    int random_num = _rnd.Next(16);
                    if (random_num >= 10)
                    {
                        gameid[i] = (char)(random_num - 10 + (int)'a');
                    }
                    else
                    {
                        gameid[i] = (char)(random_num + (int)'0');
                    }
                }
                roomidStr = new string(gameid);
            } while (!_games.TryAdd(roomidStr, game));
            game.Id = roomidStr;

            // TODO time limit

            // Start game
            game.StartGame(player1, player2);

            // TODO two AI loop

            return game;
        }
        
        /// <summary>
        /// Get the game instance by id
        /// </summary>
        /// <param name="gameid"></param>
        /// <returns>Game instance or null if the id doesn't exist</returns>
        public Pp9kGame GetGame(string gameid)
        {
            Pp9kGame game = null;
            if (!_games.TryGetValue(gameid, out game))
            {
                return null;
            }
            
            return game;
        }
    }
}
