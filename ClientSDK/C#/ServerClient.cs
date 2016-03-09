using System;
using System.Threading;

public partial class ServerClient : NetClient
{
    private const int mVersion = 0x00010000;

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

    private int mPing = 0;
    private int mGUID = 0;
    private int mFlags = 0; 

    public override bool Connect(string ip, int port)
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

    public override bool Disconnect()
    {
        if (base.Disconnect())
        {
            mThreadHeart.Abort();
            mEventHeart = null;

            return true;
        }

        return false;
    }

    public int GetPing()
    {
        return mPing;
    }

    public int GetGUID()
    {
        return mGUID;
    }

    public int GetFlags()
    {
        return mFlags;
    }

    private void SendProto(Client.REQUEST_MSG msg, global::ProtoBuf.IExtensible proto)
    {
        if (IsConnected())
        {
            Package package = new Package();
            package.buffer = ProtoHelper.ToArray((short)msg, proto);
            package.size = (short)package.buffer.Length;
            Send(package);
        }
    }
}
