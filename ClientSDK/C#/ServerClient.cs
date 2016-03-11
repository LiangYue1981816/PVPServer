using System;
using System.Threading;
using System.Collections.Generic;

public partial class ServerClient : NetClient
{
    public delegate void OnResponseLogin();
    public delegate void OnResponseCreateGame();
    public delegate void OnResponseDestroyGame();
    public delegate void OnResposneEnterGame(uint guid);
    public delegate void OnResponseExitGame(uint guid);
    public delegate void OnResponseSendToPlayer(int size, byte[] data);
    public OnResponseLogin onResponseLogin = null;
    public OnResponseCreateGame onResponseCreateGame = null;
    public OnResponseDestroyGame onResponseDestroyGame = null;
    public OnResposneEnterGame onResposneEnterGame = null;
    public OnResponseExitGame onResponseExitGame = null;
    public OnResponseSendToPlayer onResponseSendToPlayer = null;

    private ErrorCode.Code mErrorCode = ErrorCode.Code.ERR_NONE;

    private int mPing = 0;
    private uint mGUID = 0xffffffff;
    private uint mGameID = 0xffffffff;
    private uint mFlags = (uint)FlagsCode.Code.PLAYER_FLAGS_NONE;
    private List<uint> mPlayers = new List<uint>();

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
        mGameID = 0xffffffff;
        mFlags = (uint)FlagsCode.Code.PLAYER_FLAGS_NONE;

        if (base.Disconnect())
        {
            mThreadHeart.Abort();
            mEventHeart = null;

            return true;
        }

        return false;
    }

    public ErrorCode.Code GetLastError()
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

    public bool IsLogin()
    {
        return IsEnable(FlagsCode.Code.PLAYER_FLAGS_LOGIN);
    }

    public bool IsWaiting()
    {
        return IsEnable(FlagsCode.Code.PLAYER_FLAGS_WAITING);
    }

    public bool IsReady()
    {
        return IsEnable(FlagsCode.Code.PLAYER_FLAGS_READY);
    }

    public bool IsGaming()
    {
        return IsEnable(FlagsCode.Code.PLAYER_FLAGS_GAMING);
    }

    protected bool IsEnable(FlagsCode.Code code)
    {
        return (mFlags & ((uint)code)) != 0 ? true : false;
    }

    protected void ClearFlags()
    {
        mFlags = (uint)FlagsCode.Code.PLAYER_FLAGS_NONE;
    }

    protected void EnableFlag(FlagsCode.Code code)
    {
        mFlags = mFlags | ((uint)code);
    }

    protected void DisableFlag(FlagsCode.Code code)
    {
        mFlags = mFlags & ~((uint)code);
    }

    protected void SendProto(Client.REQUEST_MSG msg, global::ProtoBuf.IExtensible proto)
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
