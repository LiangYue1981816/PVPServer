using System;
using System.Threading;
using System.Collections.Generic;

public partial class ServerClient : NetClient
{
    public delegate void OnResponseError(ProtoGameServer.ERROR_CODE err);
    public delegate void OnResponseLogin();
    public delegate void OnResponseListGame(ProtoGameServer.ListGame responseListGame);
    public delegate void OnResponseCreateGame();
    public delegate void OnResponseDestroyGame();
    public delegate void OnResposneEnterGame(uint guid);
    public delegate void OnResponseExitGame(uint guid);
    public delegate void OnResponseSendToPlayer(int size, byte[] data);

    public OnResponseError onResponseError = null;
    public OnResponseLogin onResponseLogin = null;
    public OnResponseListGame onResponseListGame = null;
    public OnResponseCreateGame onResponseCreateGame = null;
    public OnResponseDestroyGame onResponseDestroyGame = null;
    public OnResposneEnterGame onResposneEnterGame = null;
    public OnResponseExitGame onResponseExitGame = null;
    public OnResponseSendToPlayer onResponseSendToPlayer = null;

    private ProtoGameServer.ERROR_CODE mErrorCode = ProtoGameServer.ERROR_CODE.ERR_NONE;

    private int mPing = 0;
    private uint mGUID = 0xffffffff;
    private uint mHostGUID = 0xcccccccc;
    private uint mGameID = 0xcccccccc;
    private uint mFlags = (uint)ProtoGameServer.FLAGS_CODE.PLAYER_FLAGS_NONE;
    private List<uint> mPlayers = new List<uint>();

    private float mHeartDeltaTime = 0.0f;

    private ProtoGameClient.Heart mRequestHeart = new ProtoGameClient.Heart();
    private ProtoGameClient.Flags mRequestFlags = new ProtoGameClient.Flags();
    private ProtoGameClient.Login mRequestLogin = new ProtoGameClient.Login();
    private ProtoGameClient.Ready mRequestReady = new ProtoGameClient.Ready();
    private ProtoGameClient.Waiting mRequestWaiting = new ProtoGameClient.Waiting();
    private ProtoGameClient.ListGame mRequestListGame = new ProtoGameClient.ListGame();
    private ProtoGameClient.CreateGame mRequestCreateGame = new ProtoGameClient.CreateGame();
    private ProtoGameClient.DestroyGame mRequestDestroyGame = new ProtoGameClient.DestroyGame();
    private ProtoGameClient.EnterGame mRequestEnterGame = new ProtoGameClient.EnterGame();
    private ProtoGameClient.ExitGame mRequestExitGame = new ProtoGameClient.ExitGame();
    private ProtoGameClient.SendToPlayer mRequestSendToPlayer = new ProtoGameClient.SendToPlayer();
    private ProtoGameClient.SendToPlayerAll mRequestSendToPlayerAll = new ProtoGameClient.SendToPlayerAll();

    public override bool Connect(string ip, int port)
    {
        return base.Connect(ip, port);
    }

    public override bool Disconnect()
    {
        mGUID = 0xffffffff;
        mHostGUID = 0xcccccccc;
        mGameID = 0xcccccccc;
        mFlags = (uint)ProtoGameServer.FLAGS_CODE.PLAYER_FLAGS_NONE;

        return base.Disconnect();
    }

    public ProtoGameServer.ERROR_CODE GetLastError()
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

    public uint GetGameID()
    {
        return mGameID;
    }

    public uint GetFlags()
    {
        return mFlags;
    }

    public bool IsHost()
    {
        return mGUID == mHostGUID;
    }

    public bool IsLogin()
    {
        return IsEnable(ProtoGameServer.FLAGS_CODE.PLAYER_FLAGS_LOGIN);
    }

    public bool IsWaiting()
    {
        return IsEnable(ProtoGameServer.FLAGS_CODE.PLAYER_FLAGS_WAITING);
    }

    public bool IsReady()
    {
        return IsEnable(ProtoGameServer.FLAGS_CODE.PLAYER_FLAGS_READY);
    }

    public bool IsGaming()
    {
        return IsEnable(ProtoGameServer.FLAGS_CODE.PLAYER_FLAGS_GAMING);
    }

    protected bool IsEnable(ProtoGameServer.FLAGS_CODE code)
    {
        return (mFlags & ((uint)code)) != 0 ? true : false;
    }

    protected void EnableFlag(ProtoGameServer.FLAGS_CODE code)
    {
        mFlags = mFlags | ((uint)code);
    }

    protected void DisableFlag(ProtoGameServer.FLAGS_CODE code)
    {
        mFlags = mFlags & ~((uint)code);
    }

    protected void SendProto(ProtoGameClient.REQUEST_MSG msg, global::ProtoBuf.IExtensible proto)
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
