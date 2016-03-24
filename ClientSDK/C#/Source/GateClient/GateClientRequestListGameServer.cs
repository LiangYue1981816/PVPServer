using System;

public partial class GateClient : NetClient
{
    public virtual void RequestListGameServer()
    {
        SendProto(ProtoGateClient.REQUEST_MSG.LIST_GAME_SERVER, mRequestListGameServer);
    }

    public virtual void ResponseListGameServer(byte[] buffer)
    {
        try
        {
            ProtoGateServer.ListGameServer responseListGameServer = ProtoHelper.ToProto<ProtoGateServer.ListGameServer>(buffer);

            if (onResponseListGameServer != null)
            {
                onResponseListGameServer(responseListGameServer);
            }
        }
        catch(Exception)
        {
        }
    }
}
