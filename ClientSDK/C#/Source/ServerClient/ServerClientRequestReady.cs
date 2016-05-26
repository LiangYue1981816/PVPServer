public partial class ServerClient : NetClient
{
    public virtual void RequestReady(bool bReady)
    {
        mRequestReady.ready = bReady;
        SendProto(ProtoGameClient.REQUEST_MSG.READY, mRequestReady);
    }
}
