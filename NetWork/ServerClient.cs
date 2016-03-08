using System;
using System.Threading;

public class ServerClient : NetClient
{
    private Thread mThreadHeart = null;
    private ManualResetEvent mEventHeart = null;

    private Client.Heart mRequestHeart = new Client.Heart();
    private Client.Flags mRequestFlags = new Client.Flags();
    private Client.Login mRequestLogin = new Client.Login();
    private Client.CreateGame mRequestCreateGame = new Client.CreateGame();
    private Client.DestroyGame mRequestDestroyGame = new Client.DestroyGame();
    private Client.EnterGame mRequestEnterGame = new Client.EnterGame();
    private Client.ExitGame mRequestExitGame = new Client.ExitGame();
    private Client.SendToPlayer mRequestSendToPlayer = new Client.SendToPlayer();
    private Client.SendToPlayerAll mRequestSendToPlayerAll = new Client.SendToPlayerAll();

    override public bool Connect(string ip, int port)
    {
        if (base.Connect(ip, port))
        {
            mThreadHeart = new Thread(ThreadHeart);
            mEventHeart = new ManualResetEvent(false);

            mThreadHeart.Start();
            mEventHeart.Set();

            return true;
        }

        return false;
    }

    private void ThreadHeart()
    {
        while (true)
        {
            mEventHeart.WaitOne();

            if (IsValid())
            {
                Thread.Sleep(1000);
                continue;
            }

            break;
        }
    }
}
