using System.Threading;

public partial class ServerClient : NetClient
{
    public override void Update(float deltaTime)
    {
        //
        // 1. Check
        //
        if (IsConnected() == false)
        {
            return;
        }

        //
        // 2. Heart
        //
        mHeartDeltaTime -= deltaTime;

        if (mHeartDeltaTime < 0.0f)
        {
            mHeartDeltaTime = 1.0f;
            RequestHeart();
        }

        //
        // 3. Base update
        //
        base.Update(deltaTime);
    }
}
