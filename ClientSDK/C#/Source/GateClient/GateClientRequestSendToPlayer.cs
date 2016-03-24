using System;

public partial class GateClient : NetClient
{
    public virtual void RequestSendToPlayer(uint[] guids, int size, byte[] data)
    {
        if (guids != null)
        {
            for (int index = 0; index < guids.Length; index++)
            {
                mRequestSendToPlayer.guids.Add(guids[index]);
            }
        }

        mRequestSendToPlayer.size = size;
        mRequestSendToPlayer.data = data;
        SendProto(ProtoGateClient.REQUEST_MSG.SEND_TO_PLAYER, mRequestSendToPlayer);
    }

    public virtual void ResponseSendToPlayer(byte[] buffer)
    {
        try
        {
            ProtoGateServer.SendToPlayer responseSendToPlayer = ProtoHelper.ToProto<ProtoGateServer.SendToPlayer>(buffer);

            if (onResponseSendToPlayer != null)
            {
                onResponseSendToPlayer(responseSendToPlayer.size, responseSendToPlayer.data);
            }
        }
        catch (Exception)
        {
        }
    }
}
