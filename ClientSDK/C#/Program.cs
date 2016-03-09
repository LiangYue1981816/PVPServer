using System;
using System.IO;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

class Program
{
    static Thread mThread = null;
    static ServerClient client = new ServerClient();

    static void Main(string[] args)
    {
        mThread = new Thread(Update);
        mThread.Start();

        while (true) {
            Console.Clear();
            Console.WriteLine("GUID: " + client.GetGUID().ToString());
            Console.WriteLine("GameID: " + client.GetGameID().ToString());
            Console.WriteLine("IsLogin: " + client.IsLogin().ToString());
            Console.WriteLine("IsWaiting: " + client.IsWaiting().ToString());
            Console.WriteLine("IsReady: " + client.IsReady().ToString());
            Console.WriteLine("IsGaming: " + client.IsGaming().ToString());
            Console.WriteLine("Error: " + client.GetLastError().ToString());
            Console.WriteLine("");

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
                client.RequestLogin((uint)DateTime.Now.Millisecond);
            }
            if (input == "3")
            {
                Console.WriteLine("Input password");
                string password = Console.ReadLine();
                client.RequestCreateGame(password, 1, 2, 10);
            }
            if (input == "4")
            {
                client.RequestDestroyGame();
            }
            if (input == "5")
            {
                Console.WriteLine("Input gameid");
                string gameid = Console.ReadLine();
                Console.WriteLine("Input password");
                string password = Console.ReadLine();
                client.RequestEnterGame(password, UInt32.Parse(gameid));
            }
            if (input == "6")
            {
                client.RequestExitGame();
            }
            if (input == "7")
            {

            }
        }
    }

    static private void Update()
    {
        while (true)
        {
            Thread.Sleep(1);
            client.Update();

            Console.Title = client.GetPing().ToString();
        }
    }
}
