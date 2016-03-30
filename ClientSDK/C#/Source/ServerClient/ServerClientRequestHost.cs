using System;

public partial class ServerClient : NetClient
{
    public virtual void ResponseHost(byte[] buffer)
    {
        try
        {
            ProtoGameServer.Host responseHost = ProtoHelper.ToProto<ProtoGameServer.Host>(buffer);

            mHostGUID = responseHost.guid;

            if (onResponseHost != null)
            {
                onResponseHost(responseHost.guid);
            }
        }
        catch(Exception)
        {
        }
    }
}
