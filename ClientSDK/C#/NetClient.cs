using System;
using System.Collections;
using System.Collections.Generic;
using System.Net;
using System.Net.Sockets;
using System.Threading;

public class NetClient
{
    private Socket mSocket = null;

    private Thread mThreadRecv = null;
    private Thread mThreadSend = null;

    private Mutex mMutexRecv = null;
    private Mutex mMutexSend = null;

    private ManualResetEvent mEventRecv = null;
    private ManualResetEvent mEventSend = null;

    private List<Package> mRecvList = new List<Package>();
    private List<Package> mSendList = new List<Package>();
    private List<Package> mSendCacheList = new List<Package>();

    virtual public bool IsValid()
    {
        return mSocket != null && mSocket.Connected == true ? true : false;
    }

    virtual public bool Connect(string ip, int port)
    {
        //
        // 1. Disconnect
        //
        Disconnect();

        //
        // 2. Connect
        //
        try
        {
            IPAddress ipAddress = IPAddress.Parse(ip);
            IPEndPoint ipEndPoint = new IPEndPoint(ipAddress, port);

            mSocket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
            mSocket.Connect(ipEndPoint);
        }
        catch (Exception)
        {
            mSocket = null;
            return false;
        }

        //
        // 3. Start thread
        //
        mThreadRecv = new Thread(ThreadRecv);
        mThreadSend = new Thread(ThreadSend);

        mMutexRecv = new Mutex();
        mMutexSend = new Mutex();

        mEventRecv = new ManualResetEvent(false);
        mEventSend = new ManualResetEvent(false);

        mThreadRecv.Start();
        mThreadSend.Start();

        mEventRecv.Set();
        mEventSend.Set();

        return true;
    }

    virtual public void Disconnect()
    {
        //
        // 1. Check
        //
        if (IsValid() == false)
        {
            return;
        }

        //
        // 2. Exit thread
        //
        mThreadRecv.Abort();
        mThreadSend.Abort();

        mThreadRecv = null;
        mThreadSend = null;

        mMutexRecv = null;
        mMutexSend = null;

        mEventRecv = null;
        mEventSend = null;

        //
        // 3. Clear list
        //
        mRecvList.Clear();
        mSendList.Clear();
        mSendCacheList.Clear();

        //
        // 4. Close socket
        //
        mSocket.Close();
        mSocket = null;
    }

    public virtual void Send(Package package)
    {
        mSendCacheList.Add(package);
    }

    public virtual void Update()
    {
        //
        // 1. Check
        //
        if (IsValid() == false)
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

    private void PauseThread()
    {
        //
        // 1. Check
        //
        if (IsValid() == false)
        {
            return;
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
    }

    private void ResumeThread()
    {
        //
        // 1. Check
        //
        if (IsValid() == false)
        {
            return;
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
    }

    private void ThreadRecv()
    {
        while (true)
        {
            mEventRecv.WaitOne();

            if (IsValid())
            {
                Package package = new Package();

                //
                // 1. Read size
                //
                {
                    byte[] bytes = new byte[2];

                    int size = SocketHelper.Receive(mSocket, bytes);
                    if (size <= 0) break;

                    package.size = BitConverter.ToUInt16(bytes, 0);
                }

                //
                // 2. Read body
                //
                {
                    package.buffer = new byte[package.size];

                    int size = SocketHelper.Receive(mSocket, package.buffer);
                    if (size <= 0) break;
                }

                //
                // 3. Add to list
                //
                mMutexRecv.WaitOne();
                {
                    mRecvList.Add(package);
                }
                mMutexRecv.ReleaseMutex();

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

            if (IsValid())
            {
                Package package = null;

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
                    if (size <= 0) break;
                }

                //
                // 4. Send body
                //
                {
                    int size = SocketHelper.Send(mSocket, package.buffer);
                    if (size <= 0) break;
                }

                continue;
            }

            break;
        }
    }
}
