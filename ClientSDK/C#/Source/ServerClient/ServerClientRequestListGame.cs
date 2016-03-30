using System;

public partial class ServerClient : NetClient
{
    public virtual void RequestListGame()
    {
        SendProto(ProtoGameClient.REQUEST_MSG.LIST_GAME, mRequestListGame);
    }

    public virtual void ResponseListGame(byte[] buffer)
    {
        try
        {
            ProtoGameServer.ListGame responseListGame = ProtoHelper.ToProto<ProtoGameServer.ListGame>(buffer);

            mErrorCode = responseListGame.err;

            if (mErrorCode == ProtoGameServer.ERROR_CODE.ERR_NONE)
            {
                if (onResponseListGame != null)
                {
                    onResponseListGame(responseListGame);
                }
            }
        }
        catch(Exception)
        {
        }
    }
}
