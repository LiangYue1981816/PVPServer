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
        Server.EnterGame responseEnterGame = ProtoHelper.ToProto<Server.EnterGame>(buffer);

        mErrorCode = responseEnterGame.err;

        if (mErrorCode == ErrorCode.Code.ERR_NONE)
        {
            if (mGUID != responseEnterGame.guid)
            {
                mPlayers.Add(responseEnterGame.guid);
            }
        }
    }
}
