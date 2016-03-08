using System;
using System.IO;
using ProtoBuf;

public static class ProtoHelper
{
    //
    // To bytes
    //
    public byte[] ToArray(Int16 message, global::ProtoBuf.IExtensible proto)
    {
        MemoryStream memStream = new MemoryStream();
        ProtoBuf.Serializer.Serialize(memStream, proto);

        byte[] msg = BitConverter.GetBytes(message);
        byte[] buffer = new byte[2 + memStream.Length];
        Array.Copy(msg, 0, buffer, 0, 2);
        Array.Copy(memStream.ToArray(), 0, buffer, 2, memStream.Length);

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
