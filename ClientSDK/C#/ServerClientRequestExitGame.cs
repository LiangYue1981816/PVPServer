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

        if (mErrorCode != ErrorCode.Code.ERR_NONE)
        {
            int index = mPlayers.IndexOf(responseExitGame.guid);
            mPlayers.RemoveAt(index);
        }
    }
}
