using System;
using System.Threading;

public partial class ServerClient : NetClient
{
    private void ThreadHeart()
    {
        while (true)
        {
            mEventHeart.WaitOne();

            if (IsValid())
            {
                Thread.Sleep(1000);
                RequestHeart(DateTime.Now.Millisecond);
                continue;
            }

            break;
        }
    }
}
