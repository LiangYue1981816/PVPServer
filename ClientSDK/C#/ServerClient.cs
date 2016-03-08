using System;
using System.Threading;

public class ServerClient : NetClient
{
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

    virtual public void RequestHeart(int timestamp)
    {
        mRequestHeart.timestamp = timestamp;
        SendProto(Client.REQUEST_MSG.HEART, mRequestHeart);
    }

    virtual public void ResponseHeart(byte[] buffer)
    {

    }

    virtual public void RequestFlags()
    {
        SendProto(Client.REQUEST_MSG.FLAGS, mRequestFlags);
    }

    virtual public void ResponseFlags(byte[] buffer)
    {

    }

    virtual public void RequestLogin(int guid)
    {
        mRequestLogin.version = 0x00010000;
        mRequestLogin.guid = guid;
        SendProto(Client.REQUEST_MSG.LOGIN, mRequestLogin);
    }

    virtual public void ResponseLogin(byte[] buffer)
    {

    }

    virtual public void RequestCreateGame(string password, int mode, int map, int maxPlayers)
    {
        mRequestCreateGame.password = password;
        mRequestCreateGame.mode = mode;
        mRequestCreateGame.map = map;
        mRequestCreateGame.maxPlayers = maxPlayers;
        SendProto(Client.REQUEST_MSG.CREATE_GAME, mRequestCreateGame);
    }

    virtual public void ResponseCreateGame(byte[] buffer)
    {

    }

    virtual public void RequestDestroyGame()
    {
        SendProto(Client.REQUEST_MSG.DESTROY_GAME, mRequestDestroyGame);
    }

    virtual public void ResponseDestroyGame(byte[] buffer)
    {

    }

    virtual public void RequestEnterGame(string password, int gameid)
    {
        mRequestEnterGame.password = password;
        mRequestEnterGame.gameid = gameid;
        SendProto(Client.REQUEST_MSG.ENTER_GAME, mRequestEnterGame);
    }

    virtual public void ResponseEnterGame(byte[] buffer)
    {

    }

    virtual public void RequestExitGame()
    {
        SendProto(Client.REQUEST_MSG.EXIT_GAME, mRequestExitGame);
    }

    virtual public void ResponseExitGame(byte[] buffer)
    {

    }

    virtual public void RequestSendToPlayer(int guid, int size, byte[] data)
    {
        mRequestSendToPlayer.guid = guid;
        mRequestSendToPlayer.size = size;
        mRequestSendToPlayer.data = data;
        SendProto(Client.REQUEST_MSG.SEND_TO_PLAYER, mRequestSendToPlayer);
    }

    virtual public void RequestSendToPlayerAll(int filter, int size, byte[] data)
    {
        mRequestSendToPlayerAll.filter = filter;
        mRequestSendToPlayerAll.size = size;
        mRequestSendToPlayerAll.data = data;
        SendProto(Client.REQUEST_MSG.SEND_TO_PLAYER_ALL, mRequestSendToPlayerAll);
    }

    virtual public void ResponseSendToPlayer(byte[] buffer)
    {

    }

    private void SendProto(Client.REQUEST_MSG msg, global::ProtoBuf.IExtensible proto)
    {
        if (IsValid())
        {
            Package package = new Package();
            package.buffer = ProtoHelper.ToArray((short)msg, proto);
            package.size = (ushort)package.buffer.Length;
            Send(package);
        }
    }


    override public void ProcessProto(short msg, byte[] buffer)
    {
        switch (msg)
        {
            case (short)Server.RESPONSE_MSG.HEART:
                ResponseHeart(buffer);
                break;

            case (short)Server.RESPONSE_MSG.FLAGS:
                ResponseFlags(buffer);
                break;

            case (short)Server.RESPONSE_MSG.LOGIN:
                ResponseLogin(buffer);
                break;

            case (short)Server.RESPONSE_MSG.CREATE_GAME:
                ResponseCreateGame(buffer);
                break;

            case (short)Server.RESPONSE_MSG.DESTROY_GAME:
                ResponseDestroyGame(buffer);
                break;

            case (short)Server.RESPONSE_MSG.ENTER_GAME:
                ResponseEnterGame(buffer);
                break;

            case (short)Server.RESPONSE_MSG.EXIT_GAME:
                ResponseExitGame(buffer);
                break;

            case (short)Server.RESPONSE_MSG.SEND_TO_PLAYER:
                ResponseSendToPlayer(buffer);
                break;
        }
    }

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
