using System;
using pp9kNET;

namespace pp9kNET
{
    public class Program
    {
        
        public static void Main(string[] args)
        {
            Console.WriteLine("Hello pp9k!");

            Chloropp9kNET pp9k = new Chloropp9kNET();

            pp9k.BoardChanged += new Chloropp9kNET.ChangeBoardHandler((x, y, type, color) =>
            {
                Console.WriteLine("Changed!");
            });

            pp9k.StartGame(Player.Human, Player.Human);

            Console.Read();
        }
        
    }
}
