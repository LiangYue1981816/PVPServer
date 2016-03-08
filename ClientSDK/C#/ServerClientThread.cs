using System.Threading;

public partial class ServerClient : NetClient
{
    private void ThreadHeart()
    {
        while (true)
        {
            mEventHeart.WaitOne();

            if (IsConnected())
            {
                Thread.Sleep(1000);
                RequestHeart();
                continue;
            }

            break;
        }
    }
}
