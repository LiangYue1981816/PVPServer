public partial class ServerClient : NetClient
{
    public virtual void RequestLogin(uint guid)
    {
        mRequestLogin.version = (int)VersionCode.Code.VERSION;
        mRequestLogin.guid = guid;
        SendProto(Client.REQUEST_MSG.LOGIN, mRequestLogin);
    }

    public virtual void ResponseLogin(byte[] buffer)
    {
        Server.Login responseLogin = ProtoHelper.ToProto<Server.Login>(buffer);

        mErrorCode = responseLogin.err;

        if (mErrorCode == ErrorCode.Code.ERR_NONE)
        {
            mGUID = responseLogin.guid;
            EnableFlag(FlagsCode.Code.PLAYER_FLAGS_LOGIN);
            DisableFlag(FlagsCode.Code.PLAYER_FLAGS_WAITING);
            DisableFlag(FlagsCode.Code.PLAYER_FLAGS_READY);
            DisableFlag(FlagsCode.Code.PLAYER_FLAGS_GAMING);
        }
    }
}
