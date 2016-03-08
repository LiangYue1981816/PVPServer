public partial class ServerClient : NetClient
{
    public virtual void RequestEnterGame(string password, int gameid)
    {
        mRequestEnterGame.password = password;
        mRequestEnterGame.gameid = gameid;
        SendProto(Client.REQUEST_MSG.ENTER_GAME, mRequestEnterGame);
    }

    public virtual void ResponseEnterGame(byte[] buffer)
    {

    }
}
