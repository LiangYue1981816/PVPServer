public partial class ServerClient : NetClient
{
    public virtual void RequestDestroyGame()
    {
        SendProto(Client.REQUEST_MSG.DESTROY_GAME, mRequestDestroyGame);
    }

    public virtual void ResponseDestroyGame(byte[] buffer)
    {

    }
}
