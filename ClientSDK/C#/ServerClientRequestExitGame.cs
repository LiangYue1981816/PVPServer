public partial class ServerClient : NetClient
{
    public virtual void RequestExitGame()
    {
        SendProto(Client.REQUEST_MSG.EXIT_GAME, mRequestExitGame);
    }

    public virtual void ResponseExitGame(byte[] buffer)
    {

    }
}
