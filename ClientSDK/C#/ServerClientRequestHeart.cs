public partial class ServerClient : NetClient
{
    public virtual void RequestHeart(int timestamp)
    {
        mRequestHeart.timestamp = timestamp;
        SendProto(Client.REQUEST_MSG.HEART, mRequestHeart);
    }

    public virtual void ResponseHeart(byte[] buffer)
    {

    }
}
