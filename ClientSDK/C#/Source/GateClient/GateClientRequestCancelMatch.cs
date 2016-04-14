using System;

public partial class GateClient : NetClient
{
    public virtual void RequestCancelMatch()
    {
        SendProto(ProtoGateClient.REQUEST_MSG.CANCEL_MATCH, mRequestCancelMatch);
    }

    public virtual void ResponseCancelMatch(byte[] buffer)
    {
        try
        {
            ProtoGateServer.CancelMatch responseCancelMatch = ProtoHelper.ToProto<ProtoGateServer.CancelMatch>(buffer);

            if (onResponseCancelMatch != null)
            {
                onResponseCancelMatch();
            }
        }
        catch (Exception)
        {
        }
    }
}
