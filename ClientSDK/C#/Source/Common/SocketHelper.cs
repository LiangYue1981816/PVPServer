using System.Net.Sockets;

public static class SocketHelper
{
    public static int Receive(Socket socket, byte[] buffer)
    {
        int recvSize = 0;

        while (recvSize < buffer.Length)
        {
            int s = socket.Receive(buffer, recvSize, buffer.Length - recvSize, SocketFlags.None);
            if (s <= 0) return -1; // Error

            recvSize += s;
        }

        return recvSize;
    }

    public static int Send(Socket socket, byte[] buffer)
    {
        int sendSize = 0;

        while (sendSize < buffer.Length)
        {
            int s = socket.Send(buffer, sendSize, buffer.Length - sendSize, SocketFlags.None);
            if (s <= 0) return -1; // Error

            sendSize += s;
        }

        return sendSize;
    }
}
