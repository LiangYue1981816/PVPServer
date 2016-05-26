using System;

public partial class ServerClient : NetClient
{
    public virtual void RequestWaiting()
    {
        SendProto(ProtoGameClient.REQUEST_MSG.WAITING, mRequestWaiting);
    }
}
