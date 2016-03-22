using System;
using System.Threading;

class Program
{
    static string mGateServerIP = "127.0.0.1";
    static int mGateServerPort = 10000;

    static string mGameServerIP = "127.0.0.1";
    static int mGameServerPort = 20000;

    static Thread mThreadUpdate = null;
    static GateClient mGateClient = new GateClient();
    static GameClient mGameClient = new GameClient();
    static GameClient[][] mGameClients = new GameClient[10][];
    static string mTestString = "A great man to save another.";

    static void Main(string[] args)
    {
        mGateClient.onResponseGameServerList = OnResponseGameServerList;
        mGameClient.onResponseSendToPlayer = OnResponseSendToPlayerOutput;

        mThreadUpdate = new Thread(ThreadUpdate);
        mThreadUpdate.Start();

        while (true) {
            Console.Clear();
            Console.WriteLine("GUID: " + mGameClient.GetGUID().ToString());
            Console.WriteLine("GameID: " + mGameClient.GetGameID().ToString());
            Console.WriteLine("IsHost: " + mGameClient.IsHost().ToString());
            Console.WriteLine("IsLogin: " + mGameClient.IsLogin().ToString());
            Console.WriteLine("IsWaiting: " + mGameClient.IsWaiting().ToString());
            Console.WriteLine("IsReady: " + mGameClient.IsReady().ToString());
            Console.WriteLine("IsGaming: " + mGameClient.IsGaming().ToString());
            Console.WriteLine("Error: " + mGameClient.GetLastError().ToString());
            Console.WriteLine("");

            Console.WriteLine("[0] AutoTest");
            Console.WriteLine("[1] Connect GameServer");
            Console.WriteLine("[2] Flags");
            Console.WriteLine("[3] Login");
            Console.WriteLine("[4] CreateGame");
            Console.WriteLine("[5] DestroyGame");
            Console.WriteLine("[6] EnterGame");
            Console.WriteLine("[7] ExitGame");
            Console.WriteLine("[8] SendToPlayer");
            Console.WriteLine("[9] SendToPlayerAll");

            Console.WriteLine("[10] Connect GateServer");
            Console.WriteLine("[11] GameServerList");

            string input = Console.ReadLine();

            if (input == "0")
            {
                Console.Clear();

                for (int indexGroup = 0; indexGroup < mGameClients.Length; indexGroup++)
                {
                    mGameClients[indexGroup] = new GameClient[10];

                    for (int index = 0; index < mGameClients[indexGroup].Length; index++)
                    {
                        mGameClients[indexGroup][index] = new GameClient();
                        mGameClients[indexGroup][index].onResponseSendToPlayer = OnResponseSendToPlayer;
                    }
                }

                while (true)
                {
                    bool bConnected = true;
                    bool bLogin = true;
                    bool bCreateGame = true;
                    bool bEnterGame = true;

                    //
                    // Update
                    //
                    for (int indexGroup = 0; indexGroup < mGameClients.Length; indexGroup++)
                    {
                        for (int index = 0; index < mGameClients[indexGroup].Length; index++)
                        {
                            mGameClients[indexGroup][index].Update();
                        }
                    }

                    //
                    // Connect
                    //
                    for (int indexGroup = 0; indexGroup < mGameClients.Length; indexGroup++)
                    {
                        for (int index = 0; index < mGameClients[indexGroup].Length; index++)
                        {
                            if (mGameClients[indexGroup][index].IsConnected() == false)
                            {
                                Thread.Sleep(1);
                                mGameClients[indexGroup][index].Connect(mGameServerIP, mGameServerPort);
                                bConnected = false;
                            }
                        }
                    }
                    if (bConnected == false)
                    {
                        Console.WriteLine("Connect...");
                        continue;
                    }

                    //
                    // Login
                    //
                    for (int indexGroup = 0; indexGroup < mGameClients.Length; indexGroup++)
                    {
                        for (int index = 0; index < mGameClients[indexGroup].Length; index++)
                        {
                            if (mGameClients[indexGroup][index].IsLogin() == false)
                            {
                                Thread.Sleep(1);
                                mGameClients[indexGroup][index].RequestLogin((uint)(DateTime.Now.Millisecond + DateTime.Now.Second * 1000));
                                bLogin = false;
                            }
                        }
                    }
                    if (bLogin == false)
                    {
                        Console.WriteLine("Login...");
                        continue;
                    }

                    //
                    // Create/Enter game
                    //
                    for (int indexGroup = 0; indexGroup < mGameClients.Length; indexGroup++)
                    {
                        uint gameid = 0xcccccccc;

                        for (int index = 0; index < mGameClients[indexGroup].Length; index++)
                        {
                            if (mGameClients[indexGroup][index].IsWaiting() && 
                                mGameClients[indexGroup][index].GetGameID() != 0xcccccccc)
                            {
                                gameid = mGameClients[indexGroup][index].GetGameID();
                                break;
                            }
                        }

                        if (gameid == 0xcccccccc)
                        {
                            mGameClients[indexGroup][0].RequestCreateGame("", 1, 2, 10);
                            bCreateGame = false;
                        }
                        else
                        {
                            for (int index = 0; index < mGameClients[indexGroup].Length; index++)
                            {
                                if (mGameClients[indexGroup][index].IsWaiting() == false)
                                {
                                    Thread.Sleep(1);
                                    mGameClients[indexGroup][index].RequestEnterGame("", gameid);
                                    bEnterGame = false;
                                }
                            }
                        }
                    }
                    if (bCreateGame == false)
                    {
                        Console.WriteLine("CreateGame...");
                        continue;
                    }
                    if (bEnterGame == false)
                    {
                        Console.WriteLine("EnterGame...");
                        continue;
                    }

                    //
                    // Transfer
                    //
                    for (int indexGroup = 0; indexGroup < mGameClients.Length; indexGroup++)
                    {
                        for (int index = 0; index < mGameClients[indexGroup].Length; index++)
                        {
                            byte[] data = System.Text.Encoding.Default.GetBytes(mTestString);
                            mGameClients[indexGroup][index].RequestSendToPlayerAll(0xffffffff, data.Length, data);
                        }
                    }

                    //
                    // Sleep
                    //
                    Thread.Sleep(33);
                }
            }
            if (input == "1")
            {
                mGameClient.Connect(mGameServerIP, mGameServerPort);
            }
            if (input == "2")
            {
                mGameClient.RequestFlags();
            }
            if (input == "3")
            {
                mGameClient.RequestLogin((uint)(DateTime.Now.Millisecond + DateTime.Now.Second * 1000));
            }
            if (input == "4")
            {
                Console.WriteLine("Input password");
                string password = Console.ReadLine();
                mGameClient.RequestCreateGame(password, 1, 2, 10);
            }
            if (input == "5")
            {
                mGameClient.RequestDestroyGame();
            }
            if (input == "6")
            {
                Console.WriteLine("Input gameid");
                string gameid = Console.ReadLine();
                Console.WriteLine("Input password");
                string password = Console.ReadLine();
                mGameClient.RequestEnterGame(password, UInt32.Parse(gameid));
            }
            if (input == "7")
            {
                mGameClient.RequestExitGame();
            }
            if (input == "8")
            {
                Console.WriteLine("Input guid");
                string guid = Console.ReadLine();
                Console.WriteLine("Input text");
                string text = Console.ReadLine();
                byte[] data = System.Text.Encoding.Default.GetBytes(text);
                mGameClient.RequestSendToPlayer(UInt32.Parse(guid), data.Length, data);
            }
            if (input == "9")
            {
                Console.WriteLine("Input text");
                string text = Console.ReadLine();
                byte[] data = System.Text.Encoding.Default.GetBytes(text);
                mGameClient.RequestSendToPlayerAll(0xffffffff, data.Length, data);
            }
            if (input == "10")
            {
                mGateClient.Connect(mGateServerIP, mGateServerPort);
            }
            if (input == "11")
            {
                mGateClient.RequestGameServerList();
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

    static void OnResponseSendToPlayerOutput(int size, byte[] data)
    {
        string strData = System.Text.Encoding.Default.GetString(data);
        Console.WriteLine("Transfer: " + strData);
    }

    static void OnResponseGameServerList(ProtoGateServer.GameServerList responseGameServerList)
    {
        for (int indexGameServer = 0; indexGameServer < responseGameServerList.servers.Count; indexGameServer++)
        {
            Console.WriteLine("GameServer: " + responseGameServerList.servers[indexGameServer].ip + ":" + responseGameServerList.servers[indexGameServer].port);

            for (int indexGame = 0; indexGame < responseGameServerList.servers[indexGameServer].games.Count; indexGame++)
            {
                Console.WriteLine("\tGame" + responseGameServerList.servers[indexGameServer].games[indexGame].gameid + ": private = " + responseGameServerList.servers[indexGameServer].games[indexGame].@private);
                Console.WriteLine("\tGame" + responseGameServerList.servers[indexGameServer].games[indexGame].gameid + ": mode = " + responseGameServerList.servers[indexGameServer].games[indexGame].mode);
                Console.WriteLine("\tGame" + responseGameServerList.servers[indexGameServer].games[indexGame].gameid + ": map = " + responseGameServerList.servers[indexGameServer].games[indexGame].map);
                Console.WriteLine("\tGame" + responseGameServerList.servers[indexGameServer].games[indexGame].gameid + ": players = " + responseGameServerList.servers[indexGameServer].games[indexGame].playes.Count + "/" + responseGameServerList.servers[indexGameServer].games[indexGame].maxPlayers);
            }
        }
    }

    static void ThreadUpdate()
    {
        while (true)
        {
            Thread.Sleep(33);
            mGateClient.Update();
            mGameClient.Update();
            Console.Title = "GameServer:" + mGameClient.GetPing().ToString() + " " + "GateServer:" + mGateClient.GetPing().ToString();
        }
    }
}
