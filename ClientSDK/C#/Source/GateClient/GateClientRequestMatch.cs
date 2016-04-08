using System;

public partial class GateClient : NetClient
{
    public virtual void RequestMatch(float evaluation, float timeout)
    {
        mRequestMatch.evaluation = evaluation;
        mRequestMatch.timeout = timeout;
        SendProto(ProtoGateClient.REQUEST_MSG.MATCH, mRequestMatch);
    }

    public virtual void ResponseMatch(byte[] buffer)
    {
        try
        {
            ProtoGateServer.Match responseMatch = ProtoHelper.ToProto<ProtoGateServer.Match>(buffer);

            mErrorCode = responseMatch.err;

            if (mErrorCode == ProtoGateServer.ERROR_CODE.ERR_NONE)
            {
                if (onResponseMatch != null)
                {
                    onResponseMatch(responseMatch.ip, responseMatch.port, responseMatch.gameid);
                }
            }
            else
            {
                if (onResponseError != null)
                {
                    onResponseError(mErrorCode);
                }
            }
        }
        catch (Exception)
        {
        }
    }
}
