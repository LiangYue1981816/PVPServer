using System;
using System.Collections;
using System.Collections.Generic;
using System.Net;
using System.Net.Sockets;
using System.Threading;

public partial class NetClient
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

    public virtual bool IsConnected()
    {
        return mSocket != null && mSocket.Connected == true ? true : false;
    }

    public virtual bool Connect(string ip, int port)
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

    public virtual bool Disconnect()
    {
        //
        // 1. Check
        //
        if (IsConnected() == false)
        {
            return false;
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

        return true;
    }

    public virtual void Send(Package package)
    {
        mSendCacheList.Add(package);
    }
}
