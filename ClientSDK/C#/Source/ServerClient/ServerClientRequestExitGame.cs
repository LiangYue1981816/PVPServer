using System;

public partial class ServerClient : NetClient
{
    public virtual void RequestExitGame()
    {
        SendProto(ProtoGameClient.REQUEST_MSG.EXIT_GAME, mRequestExitGame);
    }

    public virtual void ResponseExitGame(byte[] buffer)
    {
        try
        {
            ProtoGameServer.ExitGame responseExitGame = ProtoHelper.ToProto<ProtoGameServer.ExitGame>(buffer);

            mErrorCode = responseExitGame.err;

            if (mErrorCode == ProtoGameServer.ERROR_CODE.ERR_NONE)
            {
                if (mGUID == responseExitGame.guid)
                {
                    mPlayers.Clear();
                    mGameID = 0xcccccccc;
                    mHostGUID = 0xcccccccc;
                    DisableFlag(ProtoGameServer.FLAGS_CODE.PLAYER_FLAGS_WAITING);
                    DisableFlag(ProtoGameServer.FLAGS_CODE.PLAYER_FLAGS_READY);
                    DisableFlag(ProtoGameServer.FLAGS_CODE.PLAYER_FLAGS_GAMING);
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
