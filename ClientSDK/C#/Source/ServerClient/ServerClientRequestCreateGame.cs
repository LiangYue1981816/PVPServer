using System;

public partial class ServerClient : NetClient
{
    public virtual void RequestCreateGame(string password, int mode, int mapid, int maxPlayers, float evaluation)
    {
        mRequestCreateGame.password = password;
        mRequestCreateGame.mode = mode;
        mRequestCreateGame.mapid = mapid;
        mRequestCreateGame.maxPlayers = maxPlayers;
        mRequestCreateGame.evaluation = evaluation;
        SendProto(ProtoGameClient.REQUEST_MSG.CREATE_GAME, mRequestCreateGame);
    }

    public virtual void RequestCreateGame(string password, int gameid, int mode, int mapid, int maxPlayers, float evaluation)
    {
        mRequestCreateGame.password = password;
        mRequestCreateGame.gameid = gameid;
        mRequestCreateGame.mode = mode;
        mRequestCreateGame.mapid = mapid;
        mRequestCreateGame.maxPlayers = maxPlayers;
        mRequestCreateGame.evaluation = evaluation;
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
            else
            {
                if (onResponseError != null)
                {
                    onResponseError(mErrorCode);
                }
            }
        }
        catch(Exception)
        {
        }
    }
}
