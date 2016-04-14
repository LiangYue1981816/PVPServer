using System;

public partial class ServerClient : NetClient
{
    public virtual void RequestEnterGame(string password, int gameid)
    {
        mRequestEnterGame.password = password;
        mRequestEnterGame.gameid = gameid;
        SendProto(ProtoGameClient.REQUEST_MSG.ENTER_GAME, mRequestEnterGame);
    }

    public virtual void ResponseEnterGame(byte[] buffer)
    {
        try
        {
            ProtoGameServer.EnterGame responseEnterGame = ProtoHelper.ToProto<ProtoGameServer.EnterGame>(buffer);

            mErrorCode = responseEnterGame.err;

            if (mErrorCode == ProtoGameServer.ERROR_CODE.ERR_NONE)
            {
                if (mGUID == responseEnterGame.guid)
                {
                    mGameID = responseEnterGame.gameid;
                    mHostGUID = responseEnterGame.host;
                    EnableFlag(ProtoGameServer.FLAGS_CODE.PLAYER_FLAGS_WAITING);
                    DisableFlag(ProtoGameServer.FLAGS_CODE.PLAYER_FLAGS_READY);
                    DisableFlag(ProtoGameServer.FLAGS_CODE.PLAYER_FLAGS_GAMING);
                }
                else
                {
                    if (mPlayers.IndexOf(responseEnterGame.guid) < 0)
                    {
                        mPlayers.Add(responseEnterGame.guid);
                    }
                }

                if (onResposneEnterGame != null)
                {
                    onResposneEnterGame(responseEnterGame.guid);
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
