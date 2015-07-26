using System;
using Chloropp9k;

namespace Chloropp9k
{
    public class Program
    {
        
        public static void Main(string[] args)
        {
            Console.WriteLine("Hello World!");
            
            Chloropp9kNET pp9k = new Chloropp9kNET();
            pp9k.Dispose();
            pp9k = null;
        }
        
    }
}
