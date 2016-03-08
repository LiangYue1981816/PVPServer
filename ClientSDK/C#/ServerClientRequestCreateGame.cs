public partial class ServerClient : NetClient
{
    public virtual void RequestCreateGame(string password, int mode, int map, int maxPlayers)
    {
        mRequestCreateGame.password = password;
        mRequestCreateGame.mode = mode;
        mRequestCreateGame.map = map;
        mRequestCreateGame.maxPlayers = maxPlayers;
        SendProto(Client.REQUEST_MSG.CREATE_GAME, mRequestCreateGame);
    }

    public virtual void ResponseCreateGame(byte[] buffer)
    {

    }
}
