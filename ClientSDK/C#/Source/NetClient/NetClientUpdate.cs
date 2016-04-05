using System;

public partial class NetClient
{
    public virtual void Update(float deltaTime)
    {
        //
        // 1. Check
        //
        if (IsConnected() == false)
        {
            return;
        }

        //
        // 2. Update
        //
        PauseThread();
        {
            //
            // 2.1. Process package
            //
            mMutexRecv.WaitOne();
            {
                while (mRecvList.Count > 0) {
                    //
                    // 2.1.1. Get package
                    //
                    Package package = mRecvList[0];
                    mRecvList.RemoveAt(0);

                    //
                    // 2.1.2. Parse package, package.buffer = [proto, buffer]
                    //
                    short msg = BitConverter.ToInt16(package.buffer, 0);
                    byte[] buffer = new byte[package.buffer.Length - 2];
                    Array.Copy(package.buffer, 2, buffer, 0, buffer.Length);

                    //
                    // 2.1.3. Process
                    //
                    ProcessProto(msg, buffer);

                    //
                    // 2.2.4. Release package
                    //
                    package = null;
                }
            }
            mMutexRecv.ReleaseMutex();

            //
            // 2.2. Send package
            //
            mMutexSend.WaitOne();
            {
                while (mSendCacheList.Count > 0) {
                    mSendList.Add(mSendCacheList[0]);
                    mSendCacheList.RemoveAt(0);
                }
            }
            mMutexSend.ReleaseMutex();
        }
        ResumeThread();
    }

    public virtual void ProcessProto(short msg, byte[] buffer)
    {
    }
}
