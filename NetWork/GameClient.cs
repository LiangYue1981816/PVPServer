using System;
using System.Threading;

public class GameClient : NetClient
{
    private Thread mThreadHeart = null;
    private ManualResetEvent mEventHeart = null;

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
