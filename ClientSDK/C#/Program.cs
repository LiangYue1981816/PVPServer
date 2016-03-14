﻿using System;
using System.Threading;

class Program
{
    static string ip = "10.230.72.33";
    static int port = 10000;

    static Thread mThreadUpdate = null;
    static ServerClient mClient = new ServerClient();
    static ServerClient[][] mClients = new ServerClient[10][];
    static string mTestString = "A great man to save another.";

    static void Main(string[] args)
    {
        mClient.onResponseSendToPlayer = OnResponseSendToPlayerOutput;

        mThreadUpdate = new Thread(ThreadUpdate);
        mThreadUpdate.Start();

        while (true) {
            Console.Clear();
            Console.WriteLine("GUID: " + mClient.GetGUID().ToString());
            Console.WriteLine("GameID: " + mClient.GetGameID().ToString());
            Console.WriteLine("IsLogin: " + mClient.IsLogin().ToString());
            Console.WriteLine("IsWaiting: " + mClient.IsWaiting().ToString());
            Console.WriteLine("IsReady: " + mClient.IsReady().ToString());
            Console.WriteLine("IsGaming: " + mClient.IsGaming().ToString());
            Console.WriteLine("Error: " + mClient.GetLastError().ToString());
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

                for (int indexGroup = 0; indexGroup < mClients.Length; indexGroup++)
                {
                    mClients[indexGroup] = new ServerClient[10];

                    for (int index = 0; index < mClients[indexGroup].Length; index++)
                    {
                        mClients[indexGroup][index] = new ServerClient();
                        mClients[indexGroup][index].onResponseSendToPlayer = OnResponseSendToPlayer;
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
                    for (int indexGroup = 0; indexGroup < mClients.Length; indexGroup++)
                    {
                        for (int index = 0; index < mClients[indexGroup].Length; index++)
                        {
                            mClients[indexGroup][index].Update();
                        }
                    }

                    //
                    // Connect
                    //
                    for (int indexGroup = 0; indexGroup < mClients.Length; indexGroup++)
                    {
                        for (int index = 0; index < mClients[indexGroup].Length; index++)
                        {
                            if (mClients[indexGroup][index].IsConnected() == false)
                            {
                                Thread.Sleep(1);
                                mClients[indexGroup][index].Connect(ip, port);
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
                    for (int indexGroup = 0; indexGroup < mClients.Length; indexGroup++)
                    {
                        for (int index = 0; index < mClients[indexGroup].Length; index++)
                        {
                            if (mClients[indexGroup][index].IsLogin() == false)
                            {
                                Thread.Sleep(1);
                                mClients[indexGroup][index].RequestLogin((uint)(DateTime.Now.Millisecond + DateTime.Now.Second * 1000));
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
                    // Create game
                    //
                    for (int indexGroup = 0; indexGroup < mClients.Length; indexGroup++)
                    {
                        if (mClients[indexGroup][0].IsWaiting() == false)
                        {
                            mClients[indexGroup][0].RequestCreateGame("", 1, 2, 11);
                            bCreateGame = false;
                        }
                    }
                    if (bCreateGame == false)
                    {
                        Console.WriteLine("CreateGame...");
                        continue;
                    }

                    //
                    // Enter game
                    //
                    for (int indexGroup = 0; indexGroup < mClients.Length; indexGroup++)
                    {
                        for (int index = 1; index < mClients[indexGroup].Length; index++)
                        {
                            if (mClients[indexGroup][index].IsWaiting() == false)
                            {
                                Thread.Sleep(1);
                                mClients[indexGroup][index].RequestEnterGame("", mClients[indexGroup][0].GetGameID());
                                bEnterGame = false;
                            }
                        }
                    }
                    if (bEnterGame == false)
                    {
                        Console.WriteLine("EnterGame...");
                        continue;
                    }

                    //
                    // Transfer
                    //
                    for (int indexGroup = 0; indexGroup < mClients.Length; indexGroup++)
                    {
                        for (int index = 0; index < mClients[indexGroup].Length; index++)
                        {
                            byte[] data = System.Text.Encoding.Default.GetBytes(mTestString);
                            mClients[indexGroup][index].RequestSendToPlayerAll(0xffffffff, data.Length, data);
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
                mClient.Connect(ip, port);
            }
            if (input == "2")
            {
                mClient.RequestFlags();
            }
            if (input == "3")
            {
                mClient.RequestLogin((uint)(DateTime.Now.Millisecond + DateTime.Now.Second * 1000));
            }
            if (input == "4")
            {
                Console.WriteLine("Input password");
                string password = Console.ReadLine();
                mClient.RequestCreateGame(password, 1, 2, 10);
            }
            if (input == "5")
            {
                mClient.RequestDestroyGame();
            }
            if (input == "6")
            {
                Console.WriteLine("Input gameid");
                string gameid = Console.ReadLine();
                Console.WriteLine("Input password");
                string password = Console.ReadLine();
                mClient.RequestEnterGame(password, UInt32.Parse(gameid));
            }
            if (input == "7")
            {
                mClient.RequestExitGame();
            }
            if (input == "8")
            {
                Console.WriteLine("Input guid");
                string guid = Console.ReadLine();
                Console.WriteLine("Input text");
                string text = Console.ReadLine();
                byte[] data = System.Text.Encoding.Default.GetBytes(text);
                mClient.RequestSendToPlayer(UInt32.Parse(guid), data.Length, data);
            }
            if (input == "9")
            {
                Console.WriteLine("Input text");
                string text = Console.ReadLine();
                byte[] data = System.Text.Encoding.Default.GetBytes(text);
                mClient.RequestSendToPlayerAll(0xffffffff, data.Length, data);
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

    static void ThreadUpdate()
    {
        while (true)
        {
            Thread.Sleep(33);
            mClient.Update();
            Console.Title = mClient.GetPing().ToString();
        }
    }
}
