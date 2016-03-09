public partial class ServerClient : NetClient
{
    public virtual void RequestExitGame()
    {
        SendProto(Client.REQUEST_MSG.EXIT_GAME, mRequestExitGame);
    }

    public virtual void ResponseExitGame(byte[] buffer)
    {
        Server.ExitGame responseExitGame = ProtoHelper.ToProto<Server.ExitGame>(buffer);

        mErrorCode = responseExitGame.err;

        if (mErrorCode == ErrorCode.Code.ERR_NONE)
        {
            if (mGUID == responseExitGame.guid)
            {
                mGameID = 0xffffffff;
                DisableFlag(FlagsCode.Code.PLAYER_FLAGS_WAITING);
                DisableFlag(FlagsCode.Code.PLAYER_FLAGS_READY);
                DisableFlag(FlagsCode.Code.PLAYER_FLAGS_GAMING);
            }
            else
            {
                int index = 0;
                while ((index = mPlayers.IndexOf(responseExitGame.guid)) >= 0)
                {
                    mPlayers.RemoveAt(index);
                }
            }
        }
    }
}
