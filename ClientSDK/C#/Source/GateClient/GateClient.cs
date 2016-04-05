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
    private bool mbLogin = false;

    private float mHeartDeltaTime = 0.0f;

    private ProtoGateClient.Heart mRequestHeart = new ProtoGateClient.Heart();
    private ProtoGateClient.Login mRequestLogin = new ProtoGateClient.Login();
    private ProtoGateClient.ListGameServer mRequestListGameServer = new ProtoGateClient.ListGameServer();
    private ProtoGateClient.SendToPlayer mRequestSendToPlayer = new ProtoGateClient.SendToPlayer();

    public override bool Connect(string ip, int port)
    {
        return base.Connect(ip, port);
    }

    public override bool Disconnect()
    {
        mGUID = 0xffffffff;
        mbLogin = false;

        return base.Disconnect();
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

    public bool IsLogin()
    {
        return mbLogin;
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
