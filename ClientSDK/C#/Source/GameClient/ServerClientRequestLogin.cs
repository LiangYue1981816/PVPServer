using System;

public partial class ServerClient : NetClient
{
    public virtual void RequestLogin(uint guid)
    {
        mRequestLogin.version = (int)GameServer.VERSION_NUMBER.VERSION;
        mRequestLogin.guid = guid;
        SendProto(Client.REQUEST_MSG.LOGIN, mRequestLogin);
    }

    public virtual void ResponseLogin(byte[] buffer)
    {
        try
        {
            GameServer.Login responseLogin = ProtoHelper.ToProto<GameServer.Login>(buffer);

            mErrorCode = responseLogin.err;

            if (mErrorCode == GameServer.ERROR_CODE.ERR_NONE)
            {
                mGUID = responseLogin.guid;
                mFlags = (uint)GameServer.FLAGS_CODE.PLAYER_FLAGS_LOGIN;

                if (onResponseLogin != null)
                {
                    onResponseLogin();
                }
            }
        }
        catch (Exception)
        {
        }
    }
}
