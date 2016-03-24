using System;
using System.Threading;
using System.Collections.Generic;

public partial class GateClient : NetClient
{
    public delegate void OnResponseLogin();
    public delegate void OnResponseListGameServer(ProtoGateServer.ListGameServer responseListGameServer);
    public delegate void OnResponseSendToPlayer(int size, byte[] data);
    public OnResponseLogin onResponseLogin = null;
    public OnResponseListGameServer onResponseListGameServer = null;
    public OnResponseSendToPlayer onResponseSendToPlayer = null;

    private ProtoGateServer.ERROR_CODE mErrorCode = ProtoGateServer.ERROR_CODE.ERR_NONE;

    private int mPing = 0;
    private uint mGUID = 0xffffffff;
    private uint mFlags = (uint)ProtoGateServer.FLAGS_CODE.PLAYER_FLAGS_NONE;

    private Thread mThreadHeart = null;
    private ManualResetEvent mEventHeart = null;

    private ProtoGateClient.Heart mRequestHeart = new ProtoGateClient.Heart();
    private ProtoGateClient.ListGameServer mRequestListGameServer = new ProtoGateClient.ListGameServer();

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
        mGUID = 0xffffffff;
        mFlags = (uint)ProtoGateServer.FLAGS_CODE.PLAYER_FLAGS_NONE;

        if (base.Disconnect())
        {
            mThreadHeart.Abort();
            mEventHeart = null;

            return true;
        }

        return false;
    }

    public ProtoGateServer.ERROR_CODE GetLastError()
    {
        return mErrorCode;
    }

    public int GetPing()
    {
        return mPing;
    }

    public uint GetGUID()
    {
        return mGUID;
    }

    public uint GetFlags()
    {
        return mFlags;
    }

    public bool IsLogin()
    {
        return IsEnable(ProtoGateServer.FLAGS_CODE.PLAYER_FLAGS_LOGIN);
    }

    protected bool IsEnable(ProtoGateServer.FLAGS_CODE code)
    {
        return (mFlags & ((uint)code)) != 0 ? true : false;
    }

    protected void EnableFlag(ProtoGateServer.FLAGS_CODE code)
    {
        mFlags = mFlags | ((uint)code);
    }

    protected void DisableFlag(ProtoGateServer.FLAGS_CODE code)
    {
        mFlags = mFlags & ~((uint)code);
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
