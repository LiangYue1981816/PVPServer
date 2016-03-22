using System;
using System.Threading;
using System.Collections.Generic;

public partial class GateClient : NetClient
{
    public delegate void OnResponseGameServerList(ProtoGateServer.GameServerList responseGameServerList);
    public OnResponseGameServerList onResponseGameServerList = null;

    private int mPing = 0;

    private Thread mThreadHeart = null;
    private ManualResetEvent mEventHeart = null;

    private ProtoGateClient.Heart mRequestHeart = new ProtoGateClient.Heart();
    private ProtoGateClient.GameServerList mRequestGameServerList = new ProtoGateClient.GameServerList();

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

    protected void SendProto(ProtoGateClient.REQUEST_MSG msg, global::ProtoBuf.IExtensible proto)
    {
        try
        {
            if (IsConnected())
            {
                Package package = new Package();
                package.buffer = ProtoHelper.ToArray((short)msg, proto);
                package.size = (short)package.buffer.Length;
                Send(package);
            }
        }
        catch (Exception)
        {
        }
    }
}
