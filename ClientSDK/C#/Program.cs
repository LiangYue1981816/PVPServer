using System;
using System.Threading;
using System.Collections.Generic;

class GameServerAddress
{
    public string ip = string.Empty;
    public int port = 0;
}

public partial class GameClient : ServerClient
{
}


class Program
{
    static uint mGUID = (uint)(DateTime.Now.Millisecond + DateTime.Now.Second * 1000);

    static string mGateServerIP = "127.0.0.1";
    static int mGateServerPort = 10000;

    static string mGameServerIP = "127.0.0.1";
    static int mGameServerPort = 20000;

    static string mHelloWorld = "Hello world!";

    static Thread mThreadUpdate = null;
    static GateClient mGateClient = new GateClient();
    static GameClient mGameClient = new GameClient();
    static GateClient[] mGateClients = new GateClient[100];
    static GameClient[][] mGameClients = new GameClient[5][];

    static List<GameServerAddress> mGameServerList = new List<GameServerAddress>();

    static void Main(string[] args)
    {
        mGateClient.onResponseError = OnResponseGateServerError;
        mGateClient.onResponseMatch = OnResponseMatch;
        mGateClient.onResponseListGameServer = OnResponseListGameServer;
        mGateClient.onResponseSendToPlayer = OnResponseSendToPlayer;

        mGameClient.onResponseError = OnResponseGameServerError;
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
            Console.WriteLine("[0] AutoTest");
            Console.WriteLine("[1] Connect");
            Console.WriteLine("[2] Login");
            Console.WriteLine("[3] ListGameServer");
            Console.WriteLine("[4] Match");
            Console.WriteLine("[5] SendToPlayer");
            Console.WriteLine("");

            Console.WriteLine("GameServer");
            Console.WriteLine("[10] AutoTest");
            Console.WriteLine("[11] Connect");
            Console.WriteLine("[12] Flags");
            Console.WriteLine("[13] Login");
            Console.WriteLine("[14] ListGame");
            Console.WriteLine("[15] CreateGame");
            Console.WriteLine("[16] DestroyGame");
            Console.WriteLine("[17] EnterGame");
            Console.WriteLine("[18] ExitGame");
            Console.WriteLine("[19] SendToPlayer");
            Console.WriteLine("[20] SendToPlayerAll");

            string input = Console.ReadLine();

            if (input == "0")
            {
                GateServerAutoTest();
            }
            if (input == "1")
            {
                GateServerConnect();
            }
            if (input == "2")
            {
                GateServerLogin();
            }
            if (input == "3")
            {
                GateServerListGameServer();
            }
            if (input == "4")
            {
                GateServerMatch();
            }
            if (input == "5")
            {
                GateServerSendToPlayer();
            }

            if (input == "10")
            {
                GameServerAutoTest();
            }
            if (input == "11")
            {
                GameServerConnect();
            }
            if (input == "12")
            {
                GameServerFlags();
            }
            if (input == "13")
            {
                GameServerLogin();
            }
            if (input == "14")
            {
                GameServerListGame();
            }
            if (input == "15")
            {
                GameServerCreateGame();
            }
            if (input == "16")
            {
                GameServerDestroyGame();
            }
            if (input == "17")
            {
                GameServerEnterGame();
            }
            if (input == "18")
            {
                GameServerExitGame();
            }
            if (input == "19")
            {
                GameServerSendToPlayer();
            }
            if (input == "20")
            {
                GameServerSendToPlayerAll();
            }
        }
    }

    static void GateServerAutoTest()
    {
        mGateClient.Connect(mGateServerIP, mGateServerPort);

        for (int indexPlayer = 0; indexPlayer < mGateClients.Length; indexPlayer++)
        {
            mGateClients[indexPlayer] = new GateClient();
        }

        int nLoopCount = 0;
        while (true)
        {
            nLoopCount++;
            Thread.Sleep(33);

            bool bConnected = true;
            bool bLogin = true;

            // Update
            for (int indexPlayer = 0; indexPlayer < mGateClients.Length; indexPlayer++)
            {
                mGateClients[indexPlayer].Update(33.0f / 1000.0f);
            }

            // Connect
            for (int indexPlayer = 0; indexPlayer < mGateClients.Length; indexPlayer++)
            {
                if (mGateClients[indexPlayer].IsConnected() == false)
                {
                    mGateClients[indexPlayer].Connect(mGateServerIP, mGateServerPort);
                    bConnected = false;
                }
            }
            if (bConnected == false)
            {
                Console.WriteLine("Connect..." + nLoopCount.ToString());
                continue;
            }

            // Login
            for (int indexPlayer = 0; indexPlayer < mGateClients.Length; indexPlayer++)
            {
                if (mGateClients[indexPlayer].IsLogin() == false)
                {
                    mGateClients[indexPlayer].RequestLogin((uint)(DateTime.Now.Millisecond + DateTime.Now.Second * 1000));
                    bLogin = false;
                }
            }
            if (bLogin == false)
            {
                Console.WriteLine("Login..." + nLoopCount.ToString());
                continue;
            }

            // GameServerList
            for (int indexPlayer = 0; indexPlayer < mGateClients.Length; indexPlayer++)
            {
                mGateClients[indexPlayer].RequestListGameServer();
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

    static void GateServerMatch()
    {
        Console.WriteLine("Input Evaluation ...");
        string evaluation = Console.ReadLine();
        mGateClient.RequestMatch(Int32.Parse(evaluation));
    }

    static void GateServerSendToPlayer()
    {
        Console.WriteLine("Input Text ...");
        string text = Console.ReadLine();
        byte[] data = System.Text.Encoding.Default.GetBytes(text);
        mGateClient.RequestSendToPlayer(null, data.Length, data);
    }

    static void GameServerAutoTest()
    {
        mGameClient.Connect(mGameServerIP, mGameServerPort);

        for (int indexGame = 0; indexGame < mGameClients.Length; indexGame++)
        {
            mGameClients[indexGame] = new GameClient[10];

            for (int indexPlayer = 0; indexPlayer < mGameClients[indexGame].Length; indexPlayer++)
            {
                mGameClients[indexGame][indexPlayer] = new GameClient();
                mGameClients[indexGame][indexPlayer].onResponseSendToPlayer = OnResponseSendToPlayerAutoTest;
            }
        }

        int nLoopCount = 0;
        while (true)
        {
            nLoopCount++;
            Thread.Sleep(33);

            bool bConnected = true;
            bool bLogin = true;
            bool bEnter = true;

            // Update
            for (int indexGame = 0; indexGame < mGameClients.Length; indexGame++)
            {
                for (int indexPlayer = 0; indexPlayer < mGameClients[indexGame].Length; indexPlayer++)
                {
                    mGameClients[indexGame][indexPlayer].Update(33.0f / 1000.0f);
                }
            }

            // Connect
            for (int indexGame = 0; indexGame < mGameClients.Length; indexGame++)
            {
                for (int indexPlayer = 0; indexPlayer < mGameClients[indexGame].Length; indexPlayer++)
                {
                    if (mGameClients[indexGame][indexPlayer].IsConnected() == false)
                    {
                        mGameClients[indexGame][indexPlayer].Connect(mGameServerIP, mGameServerPort);
                        bConnected = false;
                    }
                }
            }
            if (bConnected == false)
            {
                Console.WriteLine("Connect..." + nLoopCount.ToString());
                continue;
            }

            // Login
            for (int indexGame = 0; indexGame < mGameClients.Length; indexGame++)
            {
                for (int indexPlayer = 0; indexPlayer < mGameClients[indexGame].Length; indexPlayer++)
                {
                    if (mGameClients[indexGame][indexPlayer].IsLogin() == false)
                    {
                        mGameClients[indexGame][indexPlayer].RequestLogin((uint)(DateTime.Now.Millisecond + DateTime.Now.Second * 1000));
                        bLogin = false;
                    }
                }
            }
            if (bLogin == false)
            {
                Console.WriteLine("Login..." + nLoopCount.ToString());
                continue;
            }

            // Create/Enter Game
            for (int indexGame = 0; indexGame < mGameClients.Length; indexGame++)
            {
                uint gameid = 0xcccccccc;
                for (int indexPlayer = 0; indexPlayer < mGameClients[indexGame].Length; indexPlayer++)
                {
                    if (mGameClients[indexGame][indexPlayer].IsWaiting() == true)
                    {
                        gameid = mGameClients[indexGame][indexPlayer].GetGameID();
                        break;
                    }
                }

                if (gameid == 0xcccccccc)
                {
                    mGameClients[indexGame][0].RequestCreateGame("", 0, 0, mGameClients[indexGame].Length, 0);
                    bEnter = false;
                }
                else
                {
                    for (int indexPlayer = 0; indexPlayer < mGameClients[indexGame].Length; indexPlayer++)
                    {
                        if (mGameClients[indexGame][indexPlayer].IsWaiting() == false)
                        {
                            mGameClients[indexGame][indexPlayer].RequestEnterGame("", (int)gameid);
                            bEnter = false;
                        }
                    }
                }
            }
            if (bEnter == false)
            {
                Console.WriteLine("Enter..." + nLoopCount.ToString());
                continue;
            }

            // Send
            for (int indexGame = 0; indexGame < mGameClients.Length; indexGame++)
            {
                for (int indexPlayer = 0; indexPlayer < mGameClients[indexGame].Length; indexPlayer++)
                {
                    byte[] data = System.Text.Encoding.Default.GetBytes(mHelloWorld);
                    mGameClients[indexGame][indexPlayer].RequestSendToPlayerAll(0xffffffff, data.Length, data);
                }
            }
        }
    }

    static void GameServerConnect()
    {
        Console.WriteLine("Input Server ID ...");

        string ip = mGameServerIP;
        int port = mGameServerPort;

        string input = Console.ReadLine();
        int id = input != string.Empty ? Int32.Parse(input) : -1;

        if (id >= 0 && id < mGameServerList.Count)
        {
            ip = mGameServerList[id].ip;
            port = mGameServerList[id].port;
        }

        mGameClient.Connect(ip, port);
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
        Console.WriteLine("Input Game ID ...");
        string gameid = Console.ReadLine();
        Console.WriteLine("Input Password ...");
        string password = Console.ReadLine();
        mGameClient.RequestCreateGame(password, gameid != string.Empty ? Int32.Parse(gameid) : -1, 1, 2, 10, 0);
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
        mGameClient.RequestEnterGame(password, gameid != string.Empty ? Int32.Parse(gameid) : -1);
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
        mGameClient.RequestSendToPlayer(guid != string.Empty ? UInt32.Parse(guid) : 0xffffffff, data.Length, data);
    }

    static void GameServerSendToPlayerAll()
    {
        Console.WriteLine("Input Text ...");
        string text = Console.ReadLine();
        byte[] data = System.Text.Encoding.Default.GetBytes(text);
        mGameClient.RequestSendToPlayerAll(0xffffffff, data.Length, data);
    }


    static void OnResponseGateServerError(ProtoGateServer.ERROR_CODE err)
    {
        Console.WriteLine("GateServer Error = " + err.ToString());
    }

    static void OnResponseGameServerError(ProtoGameServer.ERROR_CODE err)
    {
        Console.WriteLine("GameServer Error = " + err.ToString());
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
                "Game{0} private={1} mode={2} mapid={3} evaluation={4} players={5}/{6}",
                responseListGame.games[indexGame].gameid,
                responseListGame.games[indexGame].@private,
                responseListGame.games[indexGame].mode,
                responseListGame.games[indexGame].mapid,
                responseListGame.games[indexGame].evaluation,
                responseListGame.games[indexGame].curPlayers,
                responseListGame.games[indexGame].maxPlayers));
        }
    }

   static  void OnResponseMatch(string ip, int port, int gameid)
    {
        Console.WriteLine(string.Format("ip = {0} port = {1} gameid = {2}", ip, port, gameid));
    }

    static void OnResponseSendToPlayer(int size, byte[] data)
    {
        string strData = System.Text.Encoding.Default.GetString(data);
        Console.WriteLine("Transfer: " + strData);
    }

    static void OnResponseSendToPlayerAutoTest(int size, byte[] data)
    {
        string strData = System.Text.Encoding.Default.GetString(data);
        if (strData != mHelloWorld)
        {
            Console.WriteLine("Transfer Error: " + strData);
        }
    }

    static void ThreadUpdate()
    {
        while (true)
        {
            Thread.Sleep(1);
            mGateClient.Update(1.0f / 1000.0f);
            mGameClient.Update(1.0f / 1000.0f);
            Console.Title = "GameServer:" + mGameClient.GetPing().ToString() + " " + "GateServer:" + mGateClient.GetPing().ToString();
        }
    }
}
