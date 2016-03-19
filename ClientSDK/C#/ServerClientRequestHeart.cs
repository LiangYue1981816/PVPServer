using System;

public partial class ServerClient : NetClient
{
    public virtual void RequestHeart()
    {
        mRequestHeart.timestamp = (int)(DateTime.Now.Ticks / 10000);
        SendProto(Client.REQUEST_MSG.HEART, mRequestHeart);
    }

    public virtual void ResponseHeart(byte[] buffer)
    {
        try
        {
            GameServer.Heart responseHeart = ProtoHelper.ToProto<GameServer.Heart>(buffer);

            int timestamp = (int)(DateTime.Now.Ticks / 10000);
            mPing = timestamp - responseHeart.timestamp;
        }
        catch (Exception)
        {
        }
    }
}
