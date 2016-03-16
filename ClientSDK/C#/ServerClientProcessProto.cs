public partial class ServerClient : NetClient
{
    public override void ProcessProto(short msg, byte[] buffer)
    {
        switch (msg)
        {
            case (short)Server.RESPONSE_MSG.HEART:
                ResponseHeart(buffer);
                break;

            case (short)Server.RESPONSE_MSG.FLAGS:
                ResponseFlags(buffer);
                break;

            case (short)Server.RESPONSE_MSG.LOGIN:
                ResponseLogin(buffer);
                break;

            case (short)Server.RESPONSE_MSG.HOST:
                ResponseHost(buffer);
                break;

            case (short)Server.RESPONSE_MSG.CREATE_GAME:
                ResponseCreateGame(buffer);
                break;

            case (short)Server.RESPONSE_MSG.DESTROY_GAME:
                ResponseDestroyGame(buffer);
                break;

            case (short)Server.RESPONSE_MSG.ENTER_GAME:
                ResponseEnterGame(buffer);
                break;

            case (short)Server.RESPONSE_MSG.EXIT_GAME:
                ResponseExitGame(buffer);
                break;

            case (short)Server.RESPONSE_MSG.SEND_TO_PLAYER:
                ResponseSendToPlayer(buffer);
                break;
        }
    }
}
