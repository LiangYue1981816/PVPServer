public partial class ServerClient : NetClient
{
    public virtual void RequestLogin(int guid)
    {
        mRequestLogin.version = mVersion;
        mRequestLogin.guid = guid;
        SendProto(Client.REQUEST_MSG.LOGIN, mRequestLogin);
    }

    public virtual void ResponseLogin(byte[] buffer)
    {
        Server.Login responseLogin = ProtoHelper.ToProto<Server.Login>(buffer);

        if (responseLogin.err == (int)ErrorCode.ERR_NONE)
        {
            mGUID = responseLogin.guid;
        }
    }
}
