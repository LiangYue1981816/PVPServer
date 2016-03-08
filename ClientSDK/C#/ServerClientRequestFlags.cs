public partial class ServerClient : NetClient
{
    public virtual void RequestFlags()
    {
        SendProto(Client.REQUEST_MSG.FLAGS, mRequestFlags);
    }

    public virtual void ResponseFlags(byte[] buffer)
    {

    }
}
