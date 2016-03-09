public partial class ServerClient : NetClient
{
    public virtual void RequestDestroyGame()
    {
        SendProto(Client.REQUEST_MSG.DESTROY_GAME, mRequestDestroyGame);
    }

    public virtual void ResponseDestroyGame(byte[] buffer)
    {
        Server.DestroyGame responseDestroyGame = ProtoHelper.ToProto<Server.DestroyGame>(buffer);

        mErrorCode = responseDestroyGame.err;

        if (mErrorCode == ErrorCode.Code.ERR_NONE)
        {
            SetDisable(FlagsCode.Code.PLAYER_FLAGS_WAITING);
        }
    }
}
