using System;
using System.IO;
using ProtoBuf;

public static class ProtoHelper
{
    //
    // To bytes
    //
    static public byte[] ToArray(short message, global::ProtoBuf.IExtensible proto)
    {
        MemoryStream memStream = new MemoryStream();
        ProtoBuf.Serializer.Serialize(memStream, proto);

        byte[] msg = BitConverter.GetBytes(message);
        byte[] buffer = new byte[msg.Length + memStream.Length];
        Array.Copy(msg, 0, buffer, 0, msg.Length);
        Array.Copy(memStream.ToArray(), 0, buffer, msg.Length, memStream.Length);

        return buffer;
    }

    //
    // To proto
    //
    static public T ToProto<T>(byte[] buffer)
    {
        MemoryStream memStream = new MemoryStream(buffer);
        return ProtoBuf.Serializer.Deserialize<T>(memStream);
    }
}
