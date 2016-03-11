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
            Server.CreateGame responseCreateGame = ProtoHelper.ToProto<Server.CreateGame>(buffer);

            mErrorCode = responseCreateGame.err;

            if (mErrorCode == ErrorCode.Code.ERR_NONE)
            {
                mGameID = responseCreateGame.gameid;
                EnableFlag(FlagsCode.Code.PLAYER_FLAGS_WAITING);
                DisableFlag(FlagsCode.Code.PLAYER_FLAGS_READY);
                DisableFlag(FlagsCode.Code.PLAYER_FLAGS_GAMING);

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
