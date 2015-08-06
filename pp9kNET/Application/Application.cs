using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace pp9kNET
{
    public class Application
    {
        protected readonly Dictionary<string, Chloropp9kNET> _games = new Dictionary<string, Chloropp9kNET>();
        
        protected readonly Object _concurrent_lock = new Object();
        
        protected readonly Random _rnd = new Random();
        
        protected virtual int _id_length
        {
            get { return 6; }
        }
        
        public string CreateGame(Player player1, Player player2)
        {
            Chloropp9kNET pp9k;
            char[] gameid = new char[_id_length];
            string gameid_str;
            
            // Generate game id
            lock (_concurrent_lock)
            {
                do
                {
                    for (int i = 0; i < _id_length; i++)
                    {
                        int random_num = _rnd.Next(36);
                        if (random_num < 26)
                        {
                            gameid[i] = (char)(random_num + (int)'a');
                        }
                        else
                        {
                            gameid[i] = (char)(random_num - 26 + (int)'0');
                        }
                    } 
                    gameid_str = new string(gameid);
                } while (_games.ContainsKey(gameid_str));

                pp9k = new ChloroCometGame(gameid_str);
                _games.Add(gameid_str, pp9k);
            }
            
            // TODO time limit
            
            // Start game
            pp9k.StartGame(player1, player2);
            
            return gameid_str;
        }
        
        public Chloropp9kNET GetGame(string gameid)
        {
            Chloropp9kNET pp9k = null;
            if (!_games.TryGetValue(gameid, out pp9k))
            {
                return null;
            }
            
            return pp9k;
        }
    }
}
