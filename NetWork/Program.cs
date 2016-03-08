using System;
using System.IO;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

class Program
{
    static void Main(string[] args)
    {
        ServerClient client = new ServerClient();

        while (true) {
            Console.WriteLine("[0] Connect");
            Console.WriteLine("[1] Flags");
            Console.WriteLine("[2] Login");
            Console.WriteLine("[3] CreateGame");
            Console.WriteLine("[4] DestroyGame");
            Console.WriteLine("[5] EnterGame");
            Console.WriteLine("[6] ExitGame");
            Console.WriteLine("[7] SendToPlayer");
            Console.WriteLine("[8] SendToPlayerAll");

            string input = Console.ReadLine();

            if (input == "0")
            {
                client.Connect("127.0.0.1", 10000);
            }
            if (input == "1")
            {
                client.RequestFlags();
            }
            if (input == "2")
            {
                client.RequestLogin(1);
            }
            if (input == "3")
            {

            }
            if (input == "4")
            {

            }
            if (input == "5")
            {

            }
            if (input == "6")
            {

            }
            if (input == "7")
            {

            }
        }
    }
}
