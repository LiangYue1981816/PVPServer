using System;

public partial class GateClient : NetClient
{
    public virtual void RequestLogin(uint guid)
    {
        mRequestLogin.version = (int)ProtoGateServer.VERSION_NUMBER.VERSION;
        mRequestLogin.guid = guid;
        SendProto(ProtoGateClient.REQUEST_MSG.LOGIN, mRequestLogin);
    }

    public virtual void ResponseLogin(byte[] buffer)
    {
        try
        {
            ProtoGateServer.Login responseLogin = ProtoHelper.ToProto<ProtoGateServer.Login>(buffer);

            mErrorCode = responseLogin.err;

            if (mErrorCode == ProtoGateServer.ERROR_CODE.ERR_NONE)
            {
                mGUID = responseLogin.guid;
                mbLogin = true;

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
