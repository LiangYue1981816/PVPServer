public partial class GateClient : NetClient
{
    public override void ProcessProto(short msg, byte[] buffer)
    {
        switch (msg)
        {
            case (short)ProtoGateServer.RESPONSE_MSG.HEART:
                ResponseHeart(buffer);
                break;

            case (short)ProtoGateServer.RESPONSE_MSG.GAME_SERVER_LIST:
                ResponseGameServerList(buffer);
                break;
        }
    }
}
