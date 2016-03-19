using System;

public partial class ServerClient : NetClient
{
    public virtual void RequestLogin(uint guid)
    {
        mRequestLogin.version = (int)VersionCode.Code.VERSION;
        mRequestLogin.guid = guid;
        SendProto(Client.REQUEST_MSG.LOGIN, mRequestLogin);
    }

    public virtual void ResponseLogin(byte[] buffer)
    {
        try
        {
            Server.Login responseLogin = ProtoHelper.ToProto<Server.Login>(buffer);

            mErrorCode = responseLogin.err;

            if (mErrorCode == ErrorCode.Code.ERR_NONE)
            {
                mGUID = responseLogin.guid;
                mFlags = (uint)FlagsCode.Code.PLAYER_FLAGS_LOGIN;

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
