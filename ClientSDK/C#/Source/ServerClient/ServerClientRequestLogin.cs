using System;

public partial class ServerClient : NetClient
{
    public virtual void RequestLogin(uint guid)
    {
        mRequestLogin.version = (int)ProtoGameServer.VERSION_NUMBER.VERSION;
        mRequestLogin.guid = guid;
        SendProto(ProtoGameClient.REQUEST_MSG.LOGIN, mRequestLogin);
    }

    public virtual void ResponseLogin(byte[] buffer)
    {
        try
        {
            ProtoGameServer.Login responseLogin = ProtoHelper.ToProto<ProtoGameServer.Login>(buffer);

            mErrorCode = responseLogin.err;

            if (mErrorCode == ProtoGameServer.ERROR_CODE.ERR_NONE)
            {
                mGUID = responseLogin.guid;
                mFlags = (uint)ProtoGameServer.FLAGS_CODE.PLAYER_FLAGS_LOGIN;

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
