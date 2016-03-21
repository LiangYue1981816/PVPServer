using System;

public partial class ServerClient : NetClient
{
    public virtual void RequestEnterGame(string password, uint gameid)
    {
        mRequestEnterGame.password = password;
        mRequestEnterGame.gameid = gameid;
        SendProto(Client.REQUEST_MSG.ENTER_GAME, mRequestEnterGame);
    }

    public virtual void ResponseEnterGame(byte[] buffer)
    {
        try
        {
            GameServer.EnterGame responseEnterGame = ProtoHelper.ToProto<GameServer.EnterGame>(buffer);

            mErrorCode = responseEnterGame.err;

            if (mErrorCode == GameServer.ERROR_CODE.ERR_NONE)
            {
                if (mGUID == responseEnterGame.guid)
                {
                    mGameID = responseEnterGame.gameid;
                    EnableFlag(GameServer.FLAGS_CODE.PLAYER_FLAGS_WAITING);
                    DisableFlag(GameServer.FLAGS_CODE.PLAYER_FLAGS_READY);
                    DisableFlag(GameServer.FLAGS_CODE.PLAYER_FLAGS_GAMING);
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
        }
        catch (Exception)
        {
        }
    }
}
