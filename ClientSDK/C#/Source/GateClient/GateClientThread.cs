using System.Threading;

public partial class GateClient : NetClient
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
