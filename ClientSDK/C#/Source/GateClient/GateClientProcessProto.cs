public partial class GateClient : NetClient
{
    public override void ProcessProto(short msg, byte[] buffer)
    {
        switch (msg)
        {
            case (short)ProtoGateServer.RESPONSE_MSG.HEART:
                ResponseHeart(buffer);
                break;

            case (short)ProtoGateServer.RESPONSE_MSG.LOGIN:
                ResponseLogin(buffer);
                break;

            case (short)ProtoGateServer.RESPONSE_MSG.MATCH:
                ResponseMatch(buffer);
                break;

            case (short)ProtoGateServer.RESPONSE_MSG.SEND_TO_PLAYER:
                ResponseSendToPlayer(buffer);
                break;

            case (short)ProtoGateServer.RESPONSE_MSG.LIST_GAME_SERVER:
                ResponseListGameServer(buffer);
                break;
        }
    }
}
