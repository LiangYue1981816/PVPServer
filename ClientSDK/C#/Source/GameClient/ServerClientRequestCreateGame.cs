using System;

public partial class ServerClient : NetClient
{
    public virtual void RequestCreateGame(string password, int mode, int map, int maxPlayers)
    {
        mRequestCreateGame.password = password;
        mRequestCreateGame.mode = mode;
        mRequestCreateGame.map = map;
        mRequestCreateGame.maxPlayers = maxPlayers;
        SendProto(ProtoGameClient.REQUEST_MSG.CREATE_GAME, mRequestCreateGame);
    }

    public virtual void ResponseCreateGame(byte[] buffer)
    {
        try
        {
            ProtoGameServer.CreateGame responseCreateGame = ProtoHelper.ToProto<ProtoGameServer.CreateGame>(buffer);

            mErrorCode = responseCreateGame.err;

            if (mErrorCode == ProtoGameServer.ERROR_CODE.ERR_NONE)
            {
                mGameID = responseCreateGame.gameid;
                EnableFlag(ProtoGameServer.FLAGS_CODE.PLAYER_FLAGS_WAITING);
                DisableFlag(ProtoGameServer.FLAGS_CODE.PLAYER_FLAGS_READY);
                DisableFlag(ProtoGameServer.FLAGS_CODE.PLAYER_FLAGS_GAMING);

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
