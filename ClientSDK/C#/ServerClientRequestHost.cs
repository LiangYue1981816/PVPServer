﻿using System;

public partial class ServerClient : NetClient
{
    public virtual void ResponseHost(byte[] buffer)
    {
        try
        {
            GameServer.Host responseHost = ProtoHelper.ToProto<GameServer.Host>(buffer);

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
