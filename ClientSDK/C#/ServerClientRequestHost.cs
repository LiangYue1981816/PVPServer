using System;

public partial class ServerClient : NetClient
{
    public virtual void ResponseHost(byte[] buffer)
    {
        try
        {
            Server.Host responseHost = ProtoHelper.ToProto<Server.Host>(buffer);

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
