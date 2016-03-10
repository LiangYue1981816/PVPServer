using System;
using System.Threading;

class Program
{
    static string mTestString = "It takes a strong man to save himself, and a great man to save another. —— The Shawshank Redemption";
    static ServerClient[] mClients = new ServerClient[10];

    static void Main(string[] args)
    {
        for (int index = 0; index < mClients.Length; index++)
        {
            mClients[index] = new ServerClient();
            mClients[index].onResponseSendToPlayer = OnResponseSendToPlayer;
        }

        while (true) {
            Console.Clear();
            Console.WriteLine("GUID: " + mClients[0].GetGUID().ToString());
            Console.WriteLine("GameID: " + mClients[0].GetGameID().ToString());
            Console.WriteLine("IsLogin: " + mClients[0].IsLogin().ToString());
            Console.WriteLine("IsWaiting: " + mClients[0].IsWaiting().ToString());
            Console.WriteLine("IsReady: " + mClients[0].IsReady().ToString());
            Console.WriteLine("IsGaming: " + mClients[0].IsGaming().ToString());
            Console.WriteLine("Error: " + mClients[0].GetLastError().ToString());
            Console.WriteLine("");

            Console.WriteLine("[0] AutoTest");
            Console.WriteLine("[1] Connect");
            Console.WriteLine("[2] Flags");
            Console.WriteLine("[3] Login");
            Console.WriteLine("[4] CreateGame");
            Console.WriteLine("[5] DestroyGame");
            Console.WriteLine("[6] EnterGame");
            Console.WriteLine("[7] ExitGame");
            Console.WriteLine("[8] SendToPlayer");
            Console.WriteLine("[9] SendToPlayerAll");

            string input = Console.ReadLine();

            if (input == "0")
            {
                Console.Clear();

                while (true)
                {
                    bool bConnected = true;
                    bool bLogin = true;
                    bool bCreateGame = true;
                    bool bEnterGame = true;


                    for (int index = 0; index < mClients.Length; index++)
                    {
                        mClients[index].Update();
                    }


                    for (int index = 0; index < mClients.Length; index++)
                    {
                        if (mClients[index].IsConnected() == false)
                        {
                            mClients[index].Connect("127.0.0.1", 10000);
                            bConnected = false;
                        }
                    }
                    if (bConnected == false)
                    {
                        continue;
                    }

                    
                    for (int index = 0; index < mClients.Length; index++)
                    {
                        if (mClients[index].IsLogin() == false)
                        {
                            mClients[index].RequestLogin((uint)DateTime.Now.Millisecond);
                            bLogin = false;
                        }
                    }
                    if (bLogin == false)
                    {
                        continue;
                    }

                    
                    if (mClients[0].IsWaiting() == false)
                    {
                        mClients[0].RequestCreateGame("GoD", 1, 2, 10);
                        bCreateGame = false;
                    }
                    if (bCreateGame == false)
                    {
                        continue;
                    }


                    for (int index = 1; index < mClients.Length; index++)
                    {
                        if (mClients[index].IsWaiting() == false)
                        {
                            mClients[index].RequestEnterGame("GoD", mClients[0].GetGameID());
                            bEnterGame = false;
                        }
                    }
                    if (bEnterGame == false)
                    {
                        continue;
                    }


                    for (int index = 0; index < mClients.Length; index++)
                    {
                        byte[] data = System.Text.Encoding.Default.GetBytes(mTestString);
                        mClients[index].RequestSendToPlayerAll(0xffffffff, data.Length, data);
                    }

                    Thread.Sleep(33);
                }
            }
            if (input == "1")
            {
                mClients[0].Connect("127.0.0.1", 10000);
            }
            if (input == "2")
            {
                mClients[0].RequestFlags();
            }
            if (input == "3")
            {
                mClients[0].RequestLogin((uint)DateTime.Now.Millisecond);
            }
            if (input == "4")
            {
                Console.WriteLine("Input password");
                string password = Console.ReadLine();
                mClients[0].RequestCreateGame(password, 1, 2, 10);
            }
            if (input == "5")
            {
                mClients[0].RequestDestroyGame();
            }
            if (input == "6")
            {
                Console.WriteLine("Input gameid");
                string gameid = Console.ReadLine();
                Console.WriteLine("Input password");
                string password = Console.ReadLine();
                mClients[0].RequestEnterGame(password, UInt32.Parse(gameid));
            }
            if (input == "7")
            {
                mClients[0].RequestExitGame();
            }
            if (input == "8")
            {
                Console.WriteLine("Input guid");
                string guid = Console.ReadLine();
                Console.WriteLine("Input text");
                string text = Console.ReadLine();
                byte[] data = System.Text.Encoding.Default.GetBytes(text);
                mClients[0].RequestSendToPlayer(UInt32.Parse(guid), data.Length, data);
            }
            if (input == "9")
            {
                Console.WriteLine("Input text");
                string text = Console.ReadLine();
                byte[] data = System.Text.Encoding.Default.GetBytes(text);
                mClients[0].RequestSendToPlayerAll(0xffffffff, data.Length, data);
            }
        }
    }

    static void OnResponseSendToPlayer(int size, byte[] data)
    {
        string strData = System.Text.Encoding.Default.GetString(data);
        if (mTestString.GetHashCode() != strData.GetHashCode())
        {
            Console.WriteLine("Transfer fail: " + strData);
        }
    }
}
