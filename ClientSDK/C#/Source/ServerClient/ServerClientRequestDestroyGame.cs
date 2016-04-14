using System;

public partial class ServerClient : NetClient
{
    public virtual void RequestDestroyGame()
    {
        SendProto(ProtoGameClient.REQUEST_MSG.DESTROY_GAME, mRequestDestroyGame);
    }

    public virtual void ResponseDestroyGame(byte[] buffer)
    {
        try
        {
            ProtoGameServer.DestroyGame responseDestroyGame = ProtoHelper.ToProto<ProtoGameServer.DestroyGame>(buffer);

            mErrorCode = responseDestroyGame.err;

            if (mErrorCode == ProtoGameServer.ERROR_CODE.ERR_NONE)
            {
                mPlayers.Clear();
                mGameID = 0xcccccccc;
                mHostGUID = 0xcccccccc;
                DisableFlag(ProtoGameServer.FLAGS_CODE.PLAYER_FLAGS_WAITING);
                DisableFlag(ProtoGameServer.FLAGS_CODE.PLAYER_FLAGS_READY);
                DisableFlag(ProtoGameServer.FLAGS_CODE.PLAYER_FLAGS_GAMING);

                if (onResponseDestroyGame != null)
                {
                    onResponseDestroyGame();
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
        catch (Exception)
        {
        }
    }
}
