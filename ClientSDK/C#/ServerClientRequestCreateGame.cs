using System;

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
        try
        {
            GameServer.CreateGame responseCreateGame = ProtoHelper.ToProto<GameServer.CreateGame>(buffer);

            mErrorCode = responseCreateGame.err;

            if (mErrorCode == GameServer.ERROR_CODE.ERR_NONE)
            {
                mGameID = responseCreateGame.gameid;
                EnableFlag(GameServer.FLAGS_CODE.PLAYER_FLAGS_WAITING);
                DisableFlag(GameServer.FLAGS_CODE.PLAYER_FLAGS_READY);
                DisableFlag(GameServer.FLAGS_CODE.PLAYER_FLAGS_GAMING);

                if (onResponseCreateGame != null)
                {
                    onResponseCreateGame();
                }
            }
        }
        catch(Exception)
        {
        }
    }
}
