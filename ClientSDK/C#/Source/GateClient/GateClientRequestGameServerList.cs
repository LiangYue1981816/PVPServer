using System;

public partial class GateClient : NetClient
{
    public virtual void RequestGameServerList()
    {
        SendProto(ProtoGateClient.REQUEST_MSG.GAME_SERVER_LIST, mRequestGameServerList);
    }

    public virtual void ResponseGameServerList(byte[] buffer)
    {
        try
        {
            ProtoGateServer.GameServerList responseGameServerList = ProtoHelper.ToProto<ProtoGateServer.GameServerList>(buffer);

            if (onResponseGameServerList != null)
            {
                onResponseGameServerList(responseGameServerList);
            }
        }
        catch(Exception)
        {
        }
    }
}
