public partial class ServerClient : NetClient
{
    public virtual void RequestEnterGame(string password, uint gameid)
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
            if (mGUID == responseEnterGame.guid)
            {
                mGameID = responseEnterGame.gameid;
                EnableFlag(FlagsCode.Code.PLAYER_FLAGS_WAITING);
                DisableFlag(FlagsCode.Code.PLAYER_FLAGS_READY);
                DisableFlag(FlagsCode.Code.PLAYER_FLAGS_GAMING);
            }
            else
            {
                if (mPlayers.IndexOf(responseEnterGame.guid) < 0)
                {
                    mPlayers.Add(responseEnterGame.guid);
                }
            }

            if (onResposneEnterGame != null)
            {
                onResposneEnterGame(responseEnterGame.guid);
            }
        }
    }
}
