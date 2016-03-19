using System;

public partial class ServerClient : NetClient
{
    public virtual void RequestExitGame()
    {
        SendProto(Client.REQUEST_MSG.EXIT_GAME, mRequestExitGame);
    }

    public virtual void ResponseExitGame(byte[] buffer)
    {
        try
        {
            GameServer.ExitGame responseExitGame = ProtoHelper.ToProto<GameServer.ExitGame>(buffer);

            mErrorCode = responseExitGame.err;

            if (mErrorCode == GameServer.ERROR_CODE.ERR_NONE)
            {
                if (mGUID == responseExitGame.guid)
                {
                    mGameID = 0xcccccccc;
                    mHostGUID = 0xcccccccc;
                    DisableFlag(GameServer.FLAGS_CODE.PLAYER_FLAGS_WAITING);
                    DisableFlag(GameServer.FLAGS_CODE.PLAYER_FLAGS_READY);
                    DisableFlag(GameServer.FLAGS_CODE.PLAYER_FLAGS_GAMING);
                }
                else
                {
                    int index = 0;
                    while ((index = mPlayers.IndexOf(responseExitGame.guid)) >= 0)
                    {
                        mPlayers.RemoveAt(index);
                    }
                }

                if (onResponseExitGame != null)
                {
                    onResponseExitGame(responseExitGame.guid);
                }
            }
        }
        catch (Exception)
        {
        }
    }
}
