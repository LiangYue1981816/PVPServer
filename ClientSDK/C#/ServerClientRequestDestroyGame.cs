using System;

public partial class ServerClient : NetClient
{
    public virtual void RequestDestroyGame()
    {
        SendProto(Client.REQUEST_MSG.DESTROY_GAME, mRequestDestroyGame);
    }

    public virtual void ResponseDestroyGame(byte[] buffer)
    {
        try
        {
            GameServer.DestroyGame responseDestroyGame = ProtoHelper.ToProto<GameServer.DestroyGame>(buffer);

            mErrorCode = responseDestroyGame.err;

            if (mErrorCode == GameServer.ERROR_CODE.ERR_NONE)
            {
                mGameID = 0xcccccccc;
                mHostGUID = 0xcccccccc;
                DisableFlag(GameServer.FLAGS_CODE.PLAYER_FLAGS_WAITING);
                DisableFlag(GameServer.FLAGS_CODE.PLAYER_FLAGS_READY);
                DisableFlag(GameServer.FLAGS_CODE.PLAYER_FLAGS_GAMING);

                if (onResponseDestroyGame != null)
                {
                    onResponseDestroyGame();
                }
            }
        }
        catch (Exception)
        {
        }
    }
}
