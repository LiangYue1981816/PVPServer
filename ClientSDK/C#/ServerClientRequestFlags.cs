using System;

public partial class ServerClient : NetClient
{
    public virtual void RequestFlags()
    {
        SendProto(Client.REQUEST_MSG.FLAGS, mRequestFlags);
    }

    public virtual void ResponseFlags(byte[] buffer)
    {
        try
        {
            GameServer.Flags responseFlags = ProtoHelper.ToProto<GameServer.Flags>(buffer);
            mFlags = (mFlags & 0xffff0000) | (responseFlags.flags & 0x0000ffff);
        }
        catch (Exception)
        {
        }
    }
}
