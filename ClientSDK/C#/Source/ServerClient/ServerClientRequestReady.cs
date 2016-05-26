using System;

public partial class ServerClient : NetClient
{
    public virtual void RequestReady()
    {
        SendProto(ProtoGameClient.REQUEST_MSG.READY, mRequestReady);
    }
}
