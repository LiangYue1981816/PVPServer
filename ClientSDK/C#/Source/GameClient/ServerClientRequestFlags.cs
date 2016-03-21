using System;

public partial class ServerClient : NetClient
{
    public virtual void RequestFlags()
    {
        SendProto(ProtoGameClient.REQUEST_MSG.FLAGS, mRequestFlags);
    }

    public virtual void ResponseFlags(byte[] buffer)
    {
        try
        {
            ProtoGameServer.Flags responseFlags = ProtoHelper.ToProto<ProtoGameServer.Flags>(buffer);
            mFlags = (mFlags & 0xffff0000) | (responseFlags.flags & 0x0000ffff);
        }
        catch (Exception)
        {
        }
    }
}
