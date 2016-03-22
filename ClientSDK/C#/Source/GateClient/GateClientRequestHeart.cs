using System;

public partial class GateClient : NetClient
{
    public virtual void RequestHeart()
    {
        mRequestHeart.timestamp = (int)(DateTime.Now.Ticks / 10000);
        SendProto(ProtoGateClient.REQUEST_MSG.HEART, mRequestHeart);
    }

    public virtual void ResponseHeart(byte[] buffer)
    {
        try
        {
            ProtoGateServer.Heart responseHeart = ProtoHelper.ToProto<ProtoGateServer.Heart>(buffer);

            int timestamp = (int)(DateTime.Now.Ticks / 10000);
            mPing = timestamp - responseHeart.timestamp;
        }
        catch (Exception)
        {
        }
    }
}
