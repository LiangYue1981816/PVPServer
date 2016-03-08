public partial class ServerClient : NetClient
{
    public virtual void RequestLogin(int guid)
    {
        mRequestLogin.version = 0x00010000;
        mRequestLogin.guid = guid;
        SendProto(Client.REQUEST_MSG.LOGIN, mRequestLogin);
    }

    public virtual void ResponseLogin(byte[] buffer)
    {

    }
}
