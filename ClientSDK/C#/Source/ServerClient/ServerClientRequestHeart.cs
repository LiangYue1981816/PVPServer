using System;

public partial class ServerClient : NetClient
{
    public virtual void RequestHeart()
    {
        mRequestHeart.timestamp = (int)(DateTime.Now.Ticks / 10000);
        SendProto(ProtoGameClient.REQUEST_MSG.HEART, mRequestHeart);
    }

    public virtual void ResponseHeart(byte[] buffer)
    {
        try
        {
            ProtoGameServer.Heart responseHeart = ProtoHelper.ToProto<ProtoGameServer.Heart>(buffer);

            int timestamp = (int)(DateTime.Now.Ticks / 10000);
            mPing = timestamp - responseHeart.timestamp;
        }
        catch (Exception)
        {
        }
    }
}
