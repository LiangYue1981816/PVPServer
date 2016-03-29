using System;
using System.Threading;
using System.Collections.Generic;

class GameServerAddress
{
    public string ip = string.Empty;
    public int port = 0;
}

class Program
{
    static uint mGUID = (uint)(DateTime.Now.Millisecond + DateTime.Now.Second * 1000);

    static string mGateServerIP = "127.0.0.1";
    static int mGateServerPort = 10000;

    static Thread mThreadUpdate = null;
    static GateClient mGateClient = new GateClient();
    static GameClient mGameClient = new GameClient();

    static List<GameServerAddress> mGameServerList = new List<GameServerAddress>();

    static void Main(string[] args)
    {
        mGateClient.onResponseListGameServer = OnResponseListGameServer;
        mGateClient.onResponseSendToPlayer = OnResponseSendToPlayer;
        mGameClient.onResponseListGame = OnResponseListGame;
        mGameClient.onResponseSendToPlayer = OnResponseSendToPlayer;

        mThreadUpdate = new Thread(ThreadUpdate);
        mThreadUpdate.Start();

        while (true)
        {
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

            Console.WriteLine("GateServer");
            Console.WriteLine("[0] Connect");
            Console.WriteLine("[1] Login");
            Console.WriteLine("[2] ListGameServer");
            Console.WriteLine("[3] SendToPlayer");
            Console.WriteLine("");

            Console.WriteLine("GameServer");
            Console.WriteLine("[10] Connect");
            Console.WriteLine("[11] Flags");
            Console.WriteLine("[12] Login");
            Console.WriteLine("[13] ListGame");
            Console.WriteLine("[14] CreateGame");
            Console.WriteLine("[15] DestroyGame");
            Console.WriteLine("[16] EnterGame");
            Console.WriteLine("[17] ExitGame");
            Console.WriteLine("[18] SendToPlayer");
            Console.WriteLine("[19] SendToPlayerAll");

            string input = Console.ReadLine();

            if (input == "0")
            {
                GateServerConnect();
            }
            if (input == "1")
            {
                GateServerLogin();
            }
            if (input == "2")
            {
                GateServerListGameServer();
            }
            if (input == "3")
            {
                GateServerSendToPlayer();
            }

            if (input == "10")
            {
                GameServerConnect();
            }
            if (input == "11")
            {
                GameServerFlags();
            }
            if (input == "12")
            {
                GameServerLogin();
            }
            if (input == "13")
            {
                GameServerListGame();
            }
            if (input == "14")
            {
                GameServerCreateGame();
            }
            if (input == "15")
            {
                GameServerDestroyGame();
            }
            if (input == "16")
            {
                GameServerEnterGame();
            }
            if (input == "17")
            {
                GameServerExitGame();
            }
            if (input == "18")
            {
                GameServerSendToPlayer();
            }
            if (input == "19")
            {
                GameServerSendToPlayerAll();
            }
        }
    }

    static void GateServerConnect()
    {
        mGateClient.Connect(mGateServerIP, mGateServerPort);
    }

    static void GateServerLogin()
    {
        mGateClient.RequestLogin(mGUID);
    }

    static void GateServerListGameServer()
    {
        mGateClient.RequestListGameServer();
    }

    static void GateServerSendToPlayer()
    {
        Console.WriteLine("Input Text ...");
        string text = Console.ReadLine();
        byte[] data = System.Text.Encoding.Default.GetBytes(text);
        mGateClient.RequestSendToPlayer(null, data.Length, data);
    }

    static void GameServerConnect()
    {
        Console.WriteLine("Input Server ID ...");

        string input = Console.ReadLine();
        int id = Int32.Parse(input);

        if (id < 0 || id >= mGameServerList.Count)
        {
            Console.WriteLine("Invalid Server ID");
            return;
        }

        mGameClient.Connect(mGameServerList[id].ip, mGameServerList[id].port);
    }

    static void GameServerFlags()
    {
        mGameClient.RequestFlags();
    }

    static void GameServerLogin()
    {
        mGameClient.RequestLogin(mGUID);
    }

    static void GameServerListGame()
    {
        mGameClient.RequestListGame();
    }

    static void GameServerCreateGame()
    {
        Console.WriteLine("Input Password ...");
        string password = Console.ReadLine();
        mGameClient.RequestCreateGame(password, 1, 2, 10, 1.0f);
    }

    static void GameServerDestroyGame()
    {
        mGameClient.RequestDestroyGame();
    }

    static void GameServerEnterGame()
    {
        Console.WriteLine("Input Game ID ...");
        string gameid = Console.ReadLine();
        Console.WriteLine("Input Password ...");
        string password = Console.ReadLine();
        mGameClient.RequestEnterGame(password, UInt32.Parse(gameid));
    }

    static void GameServerExitGame()
    {
        mGameClient.RequestExitGame();
    }

    static void GameServerSendToPlayer()
    {
        Console.WriteLine("Input GUID ...");
        string guid = Console.ReadLine();
        Console.WriteLine("Input Text ...");
        string text = Console.ReadLine();
        byte[] data = System.Text.Encoding.Default.GetBytes(text);
        mGameClient.RequestSendToPlayer(UInt32.Parse(guid), data.Length, data);
    }

    static void GameServerSendToPlayerAll()
    {
        Console.WriteLine("Input Text ...");
        string text = Console.ReadLine();
        byte[] data = System.Text.Encoding.Default.GetBytes(text);
        mGameClient.RequestSendToPlayerAll(0xffffffff, data.Length, data);
    }


    static void OnResponseListGameServer(ProtoGateServer.ListGameServer responseListGameServer)
    {
        mGameServerList.Clear();

        for (int indexGameServer = 0; indexGameServer < responseListGameServer.servers.Count; indexGameServer++)
        {
            Console.WriteLine(string.Format(
                "GameServer{0}:{1}:{2} {3}/{4}",
                mGameServerList.Count,
                responseListGameServer.servers[indexGameServer].ip,
                responseListGameServer.servers[indexGameServer].port,
                responseListGameServer.servers[indexGameServer].curGames,
                responseListGameServer.servers[indexGameServer].maxGames));

            GameServerAddress address = new GameServerAddress();
            address.ip = responseListGameServer.servers[indexGameServer].ip;
            address.port = responseListGameServer.servers[indexGameServer].port;
            mGameServerList.Add(address);
        }
    }

    static void OnResponseListGame(ProtoGameServer.ListGame responseListGame)
    {
        for (int indexGame = 0; indexGame < responseListGame.games.Count; indexGame++)
        {
            Console.WriteLine(string.Format(
                "Game{0} private={1} mode={2} map={3} weight={4} players={5}/{6}",
                responseListGame.games[indexGame].gameid,
                responseListGame.games[indexGame].@private,
                responseListGame.games[indexGame].mode,
                responseListGame.games[indexGame].map,
                responseListGame.games[indexGame].weight,
                responseListGame.games[indexGame].curPlayers,
                responseListGame.games[indexGame].maxPlayers));
        }
    }

    static void OnResponseSendToPlayer(int size, byte[] data)
    {
        string strData = System.Text.Encoding.Default.GetString(data);
        Console.WriteLine("Transfer: " + strData);
    }

    static void ThreadUpdate()
    {
        while (true)
        {
            Thread.Sleep(1);
            mGateClient.Update();
            mGameClient.Update();
            Console.Title = "GameServer:" + mGameClient.GetPing().ToString() + " " + "GateServer:" + mGateClient.GetPing().ToString();
        }
    }
}
