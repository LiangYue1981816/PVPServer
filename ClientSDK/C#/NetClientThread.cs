using System;
using System.Threading;

public partial class NetClient
{
    protected virtual bool PauseThread()
    {
        //
        // 1. Check
        //
        if (IsConnected() == false)
        {
            return false;
        }

        //
        // 2. Pause thread
        //
        if (mEventRecv != null)
        {
            mEventRecv.Reset();
        }

        if (mEventSend != null)
        {
            mEventSend.Reset();
        }

        return true;
    }

    protected virtual bool ResumeThread()
    {
        //
        // 1. Check
        //
        if (IsConnected() == false)
        {
            return false;
        }

        //
        // 2. Resume thread
        //
        if (mEventRecv != null)
        {
            mEventRecv.Set();
        }

        if (mEventSend != null)
        {
            mEventSend.Set();
        }

        return true;
    }

    private void ThreadRecv()
    {
        while (true)
        {
            mEventRecv.WaitOne();

            if (IsConnected())
            {
                Package package = null;

                try
                {
                    package = new Package();

                    //
                    // 1. Read size
                    //
                    {
                        byte[] bytes = new byte[2];

                        int size = SocketHelper.Receive(mSocket, bytes);
                        if (size <= 0) throw new Exception();

                        package.size = BitConverter.ToInt16(bytes, 0);
                    }

                    //
                    // 2. Read body
                    //
                    {
                        package.buffer = new byte[package.size];

                        int size = SocketHelper.Receive(mSocket, package.buffer);
                        if (size <= 0) throw new Exception();
                    }

                    //
                    // 3. Add to list
                    //
                    mMutexRecv.WaitOne();
                    {
                        mRecvList.Add(package);
                    }
                    mMutexRecv.ReleaseMutex();
                }
                catch (Exception)
                {
                    package = null;
                    break;
                }

                continue;
            }

            break;
        }
    }

    private void ThreadSend()
    {
        while (true)
        {
            mEventSend.WaitOne();

            if (IsConnected())
            {
                Package package = null;

                try
                {
                    //
                    // 1. Sleep 1ms
                    //
                    Thread.Sleep(1);

                    //
                    // 2. Get package
                    //
                    mMutexSend.WaitOne();
                    {
                        if (mSendList.Count > 0)
                        {
                            package = mSendList[mSendList.Count - 1];
                            mSendList.RemoveAt(mSendList.Count - 1);
                        }
                    }
                    mMutexSend.ReleaseMutex();

                    if (package == null)
                    {
                        continue;
                    }

                    //
                    // 3. Send size
                    //
                    {
                        byte[] bytes = BitConverter.GetBytes(package.size);

                        int size = SocketHelper.Send(mSocket, bytes);
                        if (size <= 0) throw new Exception();
                    }

                    //
                    // 4. Send body
                    //
                    {
                        int size = SocketHelper.Send(mSocket, package.buffer);
                        if (size <= 0) throw new Exception();
                    }
                }
                catch (Exception)
                {
                    break;
                }
                finally
                {
                    package = null;
                }

                continue;
            }

            break;
        }
    }
}
