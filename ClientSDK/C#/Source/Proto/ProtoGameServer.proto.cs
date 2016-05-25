//------------------------------------------------------------------------------
// <auto-generated>
//     This code was generated by a tool.
//
//     Changes to this file may cause incorrect behavior and will be lost if
//     the code is regenerated.
// </auto-generated>
//------------------------------------------------------------------------------

// Generated from: ProtoGameServer.proto
namespace ProtoGameServer
{
  [global::System.Serializable, global::ProtoBuf.ProtoContract(Name=@"Heart")]
  public partial class Heart : global::ProtoBuf.IExtensible
  {
    public Heart() {}
    
    private int _timestamp;
    [global::ProtoBuf.ProtoMember(1, IsRequired = true, Name=@"timestamp", DataFormat = global::ProtoBuf.DataFormat.TwosComplement)]
    public int timestamp
    {
      get { return _timestamp; }
      set { _timestamp = value; }
    }
    private global::ProtoBuf.IExtension extensionObject;
    global::ProtoBuf.IExtension global::ProtoBuf.IExtensible.GetExtensionObject(bool createIfMissing)
      { return global::ProtoBuf.Extensible.GetExtensionObject(ref extensionObject, createIfMissing); }
  }
  
  [global::System.Serializable, global::ProtoBuf.ProtoContract(Name=@"Flags")]
  public partial class Flags : global::ProtoBuf.IExtensible
  {
    public Flags() {}
    
    private uint _flags;
    [global::ProtoBuf.ProtoMember(1, IsRequired = true, Name=@"flags", DataFormat = global::ProtoBuf.DataFormat.TwosComplement)]
    public uint flags
    {
      get { return _flags; }
      set { _flags = value; }
    }
    private global::ProtoBuf.IExtension extensionObject;
    global::ProtoBuf.IExtension global::ProtoBuf.IExtensible.GetExtensionObject(bool createIfMissing)
      { return global::ProtoBuf.Extensible.GetExtensionObject(ref extensionObject, createIfMissing); }
  }
  
  [global::System.Serializable, global::ProtoBuf.ProtoContract(Name=@"Login")]
  public partial class Login : global::ProtoBuf.IExtensible
  {
    public Login() {}
    
    private ProtoGameServer.ERROR_CODE _err;
    [global::ProtoBuf.ProtoMember(1, IsRequired = true, Name=@"err", DataFormat = global::ProtoBuf.DataFormat.TwosComplement)]
    public ProtoGameServer.ERROR_CODE err
    {
      get { return _err; }
      set { _err = value; }
    }
    private uint _guid = default(uint);
    [global::ProtoBuf.ProtoMember(2, IsRequired = false, Name=@"guid", DataFormat = global::ProtoBuf.DataFormat.TwosComplement)]
    [global::System.ComponentModel.DefaultValue(default(uint))]
    public uint guid
    {
      get { return _guid; }
      set { _guid = value; }
    }
    private global::ProtoBuf.IExtension extensionObject;
    global::ProtoBuf.IExtension global::ProtoBuf.IExtensible.GetExtensionObject(bool createIfMissing)
      { return global::ProtoBuf.Extensible.GetExtensionObject(ref extensionObject, createIfMissing); }
  }
  
  [global::System.Serializable, global::ProtoBuf.ProtoContract(Name=@"ListGame")]
  public partial class ListGame : global::ProtoBuf.IExtensible
  {
    public ListGame() {}
    
    private ProtoGameServer.ERROR_CODE _err;
    [global::ProtoBuf.ProtoMember(1, IsRequired = true, Name=@"err", DataFormat = global::ProtoBuf.DataFormat.TwosComplement)]
    public ProtoGameServer.ERROR_CODE err
    {
      get { return _err; }
      set { _err = value; }
    }
    private readonly global::System.Collections.Generic.List<ProtoGameServer.ListGame.Game> _games = new global::System.Collections.Generic.List<ProtoGameServer.ListGame.Game>();
    [global::ProtoBuf.ProtoMember(2, Name=@"games", DataFormat = global::ProtoBuf.DataFormat.Default)]
    public global::System.Collections.Generic.List<ProtoGameServer.ListGame.Game> games
    {
      get { return _games; }
    }
  
  [global::System.Serializable, global::ProtoBuf.ProtoContract(Name=@"Game")]
  public partial class Game : global::ProtoBuf.IExtensible
  {
    public Game() {}
    
    private bool _private;
    [global::ProtoBuf.ProtoMember(1, IsRequired = true, Name=@"private", DataFormat = global::ProtoBuf.DataFormat.Default)]
    public bool @private
    {
      get { return _private; }
      set { _private = value; }
    }
    private int _gameid;
    [global::ProtoBuf.ProtoMember(2, IsRequired = true, Name=@"gameid", DataFormat = global::ProtoBuf.DataFormat.TwosComplement)]
    public int gameid
    {
      get { return _gameid; }
      set { _gameid = value; }
    }
    private int _mode;
    [global::ProtoBuf.ProtoMember(3, IsRequired = true, Name=@"mode", DataFormat = global::ProtoBuf.DataFormat.TwosComplement)]
    public int mode
    {
      get { return _mode; }
      set { _mode = value; }
    }
    private int _mapid;
    [global::ProtoBuf.ProtoMember(4, IsRequired = true, Name=@"mapid", DataFormat = global::ProtoBuf.DataFormat.TwosComplement)]
    public int mapid
    {
      get { return _mapid; }
      set { _mapid = value; }
    }
    private int _curPlayers;
    [global::ProtoBuf.ProtoMember(5, IsRequired = true, Name=@"curPlayers", DataFormat = global::ProtoBuf.DataFormat.TwosComplement)]
    public int curPlayers
    {
      get { return _curPlayers; }
      set { _curPlayers = value; }
    }
    private int _maxPlayers;
    [global::ProtoBuf.ProtoMember(6, IsRequired = true, Name=@"maxPlayers", DataFormat = global::ProtoBuf.DataFormat.TwosComplement)]
    public int maxPlayers
    {
      get { return _maxPlayers; }
      set { _maxPlayers = value; }
    }
    private int _evaluation;
    [global::ProtoBuf.ProtoMember(7, IsRequired = true, Name=@"evaluation", DataFormat = global::ProtoBuf.DataFormat.TwosComplement)]
    public int evaluation
    {
      get { return _evaluation; }
      set { _evaluation = value; }
    }
    private global::ProtoBuf.IExtension extensionObject;
    global::ProtoBuf.IExtension global::ProtoBuf.IExtensible.GetExtensionObject(bool createIfMissing)
      { return global::ProtoBuf.Extensible.GetExtensionObject(ref extensionObject, createIfMissing); }
  }
  
    private global::ProtoBuf.IExtension extensionObject;
    global::ProtoBuf.IExtension global::ProtoBuf.IExtensible.GetExtensionObject(bool createIfMissing)
      { return global::ProtoBuf.Extensible.GetExtensionObject(ref extensionObject, createIfMissing); }
  }
  
  [global::System.Serializable, global::ProtoBuf.ProtoContract(Name=@"CreateGame")]
  public partial class CreateGame : global::ProtoBuf.IExtensible
  {
    public CreateGame() {}
    
    private ProtoGameServer.ERROR_CODE _err;
    [global::ProtoBuf.ProtoMember(1, IsRequired = true, Name=@"err", DataFormat = global::ProtoBuf.DataFormat.TwosComplement)]
    public ProtoGameServer.ERROR_CODE err
    {
      get { return _err; }
      set { _err = value; }
    }
    private uint _host = default(uint);
    [global::ProtoBuf.ProtoMember(2, IsRequired = false, Name=@"host", DataFormat = global::ProtoBuf.DataFormat.TwosComplement)]
    [global::System.ComponentModel.DefaultValue(default(uint))]
    public uint host
    {
      get { return _host; }
      set { _host = value; }
    }
    private uint _gameid = default(uint);
    [global::ProtoBuf.ProtoMember(3, IsRequired = false, Name=@"gameid", DataFormat = global::ProtoBuf.DataFormat.TwosComplement)]
    [global::System.ComponentModel.DefaultValue(default(uint))]
    public uint gameid
    {
      get { return _gameid; }
      set { _gameid = value; }
    }
    private global::ProtoBuf.IExtension extensionObject;
    global::ProtoBuf.IExtension global::ProtoBuf.IExtensible.GetExtensionObject(bool createIfMissing)
      { return global::ProtoBuf.Extensible.GetExtensionObject(ref extensionObject, createIfMissing); }
  }
  
  [global::System.Serializable, global::ProtoBuf.ProtoContract(Name=@"DestroyGame")]
  public partial class DestroyGame : global::ProtoBuf.IExtensible
  {
    public DestroyGame() {}
    
    private ProtoGameServer.ERROR_CODE _err;
    [global::ProtoBuf.ProtoMember(1, IsRequired = true, Name=@"err", DataFormat = global::ProtoBuf.DataFormat.TwosComplement)]
    public ProtoGameServer.ERROR_CODE err
    {
      get { return _err; }
      set { _err = value; }
    }
    private global::ProtoBuf.IExtension extensionObject;
    global::ProtoBuf.IExtension global::ProtoBuf.IExtensible.GetExtensionObject(bool createIfMissing)
      { return global::ProtoBuf.Extensible.GetExtensionObject(ref extensionObject, createIfMissing); }
  }
  
  [global::System.Serializable, global::ProtoBuf.ProtoContract(Name=@"EnterGame")]
  public partial class EnterGame : global::ProtoBuf.IExtensible
  {
    public EnterGame() {}
    
    private ProtoGameServer.ERROR_CODE _err;
    [global::ProtoBuf.ProtoMember(1, IsRequired = true, Name=@"err", DataFormat = global::ProtoBuf.DataFormat.TwosComplement)]
    public ProtoGameServer.ERROR_CODE err
    {
      get { return _err; }
      set { _err = value; }
    }
    private uint _guid = default(uint);
    [global::ProtoBuf.ProtoMember(2, IsRequired = false, Name=@"guid", DataFormat = global::ProtoBuf.DataFormat.TwosComplement)]
    [global::System.ComponentModel.DefaultValue(default(uint))]
    public uint guid
    {
      get { return _guid; }
      set { _guid = value; }
    }
    private uint _host = default(uint);
    [global::ProtoBuf.ProtoMember(3, IsRequired = false, Name=@"host", DataFormat = global::ProtoBuf.DataFormat.TwosComplement)]
    [global::System.ComponentModel.DefaultValue(default(uint))]
    public uint host
    {
      get { return _host; }
      set { _host = value; }
    }
    private uint _gameid = default(uint);
    [global::ProtoBuf.ProtoMember(4, IsRequired = false, Name=@"gameid", DataFormat = global::ProtoBuf.DataFormat.TwosComplement)]
    [global::System.ComponentModel.DefaultValue(default(uint))]
    public uint gameid
    {
      get { return _gameid; }
      set { _gameid = value; }
    }
    private global::ProtoBuf.IExtension extensionObject;
    global::ProtoBuf.IExtension global::ProtoBuf.IExtensible.GetExtensionObject(bool createIfMissing)
      { return global::ProtoBuf.Extensible.GetExtensionObject(ref extensionObject, createIfMissing); }
  }
  
  [global::System.Serializable, global::ProtoBuf.ProtoContract(Name=@"ExitGame")]
  public partial class ExitGame : global::ProtoBuf.IExtensible
  {
    public ExitGame() {}
    
    private ProtoGameServer.ERROR_CODE _err;
    [global::ProtoBuf.ProtoMember(1, IsRequired = true, Name=@"err", DataFormat = global::ProtoBuf.DataFormat.TwosComplement)]
    public ProtoGameServer.ERROR_CODE err
    {
      get { return _err; }
      set { _err = value; }
    }
    private uint _guid = default(uint);
    [global::ProtoBuf.ProtoMember(2, IsRequired = false, Name=@"guid", DataFormat = global::ProtoBuf.DataFormat.TwosComplement)]
    [global::System.ComponentModel.DefaultValue(default(uint))]
    public uint guid
    {
      get { return _guid; }
      set { _guid = value; }
    }
    private uint _host = default(uint);
    [global::ProtoBuf.ProtoMember(3, IsRequired = false, Name=@"host", DataFormat = global::ProtoBuf.DataFormat.TwosComplement)]
    [global::System.ComponentModel.DefaultValue(default(uint))]
    public uint host
    {
      get { return _host; }
      set { _host = value; }
    }
    private global::ProtoBuf.IExtension extensionObject;
    global::ProtoBuf.IExtension global::ProtoBuf.IExtensible.GetExtensionObject(bool createIfMissing)
      { return global::ProtoBuf.Extensible.GetExtensionObject(ref extensionObject, createIfMissing); }
  }
  
  [global::System.Serializable, global::ProtoBuf.ProtoContract(Name=@"SendToPlayer")]
  public partial class SendToPlayer : global::ProtoBuf.IExtensible
  {
    public SendToPlayer() {}
    
    private int _size;
    [global::ProtoBuf.ProtoMember(1, IsRequired = true, Name=@"size", DataFormat = global::ProtoBuf.DataFormat.TwosComplement)]
    public int size
    {
      get { return _size; }
      set { _size = value; }
    }
    private byte[] _data;
    [global::ProtoBuf.ProtoMember(2, IsRequired = true, Name=@"data", DataFormat = global::ProtoBuf.DataFormat.Default)]
    public byte[] data
    {
      get { return _data; }
      set { _data = value; }
    }
    private global::ProtoBuf.IExtension extensionObject;
    global::ProtoBuf.IExtension global::ProtoBuf.IExtensible.GetExtensionObject(bool createIfMissing)
      { return global::ProtoBuf.Extensible.GetExtensionObject(ref extensionObject, createIfMissing); }
  }
  
  [global::System.Serializable, global::ProtoBuf.ProtoContract(Name=@"ServerStatus")]
  public partial class ServerStatus : global::ProtoBuf.IExtensible
  {
    public ServerStatus() {}
    
    private string _ip;
    [global::ProtoBuf.ProtoMember(1, IsRequired = true, Name=@"ip", DataFormat = global::ProtoBuf.DataFormat.Default)]
    public string ip
    {
      get { return _ip; }
      set { _ip = value; }
    }
    private int _port;
    [global::ProtoBuf.ProtoMember(2, IsRequired = true, Name=@"port", DataFormat = global::ProtoBuf.DataFormat.TwosComplement)]
    public int port
    {
      get { return _port; }
      set { _port = value; }
    }
    private int _curGames;
    [global::ProtoBuf.ProtoMember(3, IsRequired = true, Name=@"curGames", DataFormat = global::ProtoBuf.DataFormat.TwosComplement)]
    public int curGames
    {
      get { return _curGames; }
      set { _curGames = value; }
    }
    private int _maxGames;
    [global::ProtoBuf.ProtoMember(4, IsRequired = true, Name=@"maxGames", DataFormat = global::ProtoBuf.DataFormat.TwosComplement)]
    public int maxGames
    {
      get { return _maxGames; }
      set { _maxGames = value; }
    }
    private readonly global::System.Collections.Generic.List<ProtoGameServer.ServerStatus.Game> _games = new global::System.Collections.Generic.List<ProtoGameServer.ServerStatus.Game>();
    [global::ProtoBuf.ProtoMember(5, Name=@"games", DataFormat = global::ProtoBuf.DataFormat.Default)]
    public global::System.Collections.Generic.List<ProtoGameServer.ServerStatus.Game> games
    {
      get { return _games; }
    }
  
  [global::System.Serializable, global::ProtoBuf.ProtoContract(Name=@"Game")]
  public partial class Game : global::ProtoBuf.IExtensible
  {
    public Game() {}
    
    private bool _empty;
    [global::ProtoBuf.ProtoMember(1, IsRequired = true, Name=@"empty", DataFormat = global::ProtoBuf.DataFormat.Default)]
    public bool empty
    {
      get { return _empty; }
      set { _empty = value; }
    }
    private int _gameid;
    [global::ProtoBuf.ProtoMember(2, IsRequired = true, Name=@"gameid", DataFormat = global::ProtoBuf.DataFormat.TwosComplement)]
    public int gameid
    {
      get { return _gameid; }
      set { _gameid = value; }
    }
    private int _mode;
    [global::ProtoBuf.ProtoMember(3, IsRequired = true, Name=@"mode", DataFormat = global::ProtoBuf.DataFormat.TwosComplement)]
    public int mode
    {
      get { return _mode; }
      set { _mode = value; }
    }
    private int _mapid;
    [global::ProtoBuf.ProtoMember(4, IsRequired = true, Name=@"mapid", DataFormat = global::ProtoBuf.DataFormat.TwosComplement)]
    public int mapid
    {
      get { return _mapid; }
      set { _mapid = value; }
    }
    private int _evaluation;
    [global::ProtoBuf.ProtoMember(5, IsRequired = true, Name=@"evaluation", DataFormat = global::ProtoBuf.DataFormat.TwosComplement)]
    public int evaluation
    {
      get { return _evaluation; }
      set { _evaluation = value; }
    }
    private global::ProtoBuf.IExtension extensionObject;
    global::ProtoBuf.IExtension global::ProtoBuf.IExtensible.GetExtensionObject(bool createIfMissing)
      { return global::ProtoBuf.Extensible.GetExtensionObject(ref extensionObject, createIfMissing); }
  }
  
    private global::ProtoBuf.IExtension extensionObject;
    global::ProtoBuf.IExtension global::ProtoBuf.IExtensible.GetExtensionObject(bool createIfMissing)
      { return global::ProtoBuf.Extensible.GetExtensionObject(ref extensionObject, createIfMissing); }
  }
  
    [global::ProtoBuf.ProtoContract(Name=@"VERSION_NUMBER")]
    public enum VERSION_NUMBER
    {
            
      [global::ProtoBuf.ProtoEnum(Name=@"VERSION", Value=65536)]
      VERSION = 65536
    }
  
    [global::ProtoBuf.ProtoContract(Name=@"FLAGS_CODE")]
    public enum FLAGS_CODE
    {
            
      [global::ProtoBuf.ProtoEnum(Name=@"PLAYER_FLAGS_NONE", Value=0)]
      PLAYER_FLAGS_NONE = 0,
            
      [global::ProtoBuf.ProtoEnum(Name=@"PLAYER_FLAGS_LOGIN", Value=1)]
      PLAYER_FLAGS_LOGIN = 1,
            
      [global::ProtoBuf.ProtoEnum(Name=@"PLAYER_FLAGS_WAITING", Value=2)]
      PLAYER_FLAGS_WAITING = 2,
            
      [global::ProtoBuf.ProtoEnum(Name=@"PLAYER_FLAGS_READY", Value=4)]
      PLAYER_FLAGS_READY = 4,
            
      [global::ProtoBuf.ProtoEnum(Name=@"PLAYER_FLAGS_GAMING", Value=8)]
      PLAYER_FLAGS_GAMING = 8
    }
  
    [global::ProtoBuf.ProtoContract(Name=@"ERROR_CODE")]
    public enum ERROR_CODE
    {
            
      [global::ProtoBuf.ProtoEnum(Name=@"ERR_NONE", Value=0)]
      ERR_NONE = 0,
            
      [global::ProtoBuf.ProtoEnum(Name=@"ERR_VERSION_INVALID", Value=1)]
      ERR_VERSION_INVALID = 1,
            
      [global::ProtoBuf.ProtoEnum(Name=@"ERR_PLAYER_INVALID", Value=1000)]
      ERR_PLAYER_INVALID = 1000,
            
      [global::ProtoBuf.ProtoEnum(Name=@"ERR_PLAYER_INVALID_GUID", Value=1001)]
      ERR_PLAYER_INVALID_GUID = 1001,
            
      [global::ProtoBuf.ProtoEnum(Name=@"ERR_PLAYER_FLAGS_NOT_NONE", Value=1002)]
      ERR_PLAYER_FLAGS_NOT_NONE = 1002,
            
      [global::ProtoBuf.ProtoEnum(Name=@"ERR_PLAYER_FLAGS_NOT_LOGIN", Value=1003)]
      ERR_PLAYER_FLAGS_NOT_LOGIN = 1003,
            
      [global::ProtoBuf.ProtoEnum(Name=@"ERR_PLAYER_FLAGS_NOT_INGAME", Value=1004)]
      ERR_PLAYER_FLAGS_NOT_INGAME = 1004,
            
      [global::ProtoBuf.ProtoEnum(Name=@"ERR_PLAYER_FLAGS_INGAME", Value=1005)]
      ERR_PLAYER_FLAGS_INGAME = 1005,
            
      [global::ProtoBuf.ProtoEnum(Name=@"ERR_PLAYER_NOT_HOST", Value=1006)]
      ERR_PLAYER_NOT_HOST = 1006,
            
      [global::ProtoBuf.ProtoEnum(Name=@"ERR_GAME_INVALID", Value=2000)]
      ERR_GAME_INVALID = 2000,
            
      [global::ProtoBuf.ProtoEnum(Name=@"ERR_GAME_INVALID_ID", Value=2001)]
      ERR_GAME_INVALID_ID = 2001,
            
      [global::ProtoBuf.ProtoEnum(Name=@"ERR_GAME_USING", Value=2002)]
      ERR_GAME_USING = 2002,
            
      [global::ProtoBuf.ProtoEnum(Name=@"ERR_GAME_EMPTY", Value=2003)]
      ERR_GAME_EMPTY = 2003,
            
      [global::ProtoBuf.ProtoEnum(Name=@"ERR_GAME_FULL", Value=2004)]
      ERR_GAME_FULL = 2004,
            
      [global::ProtoBuf.ProtoEnum(Name=@"ERR_GAME_PASSWORD", Value=2005)]
      ERR_GAME_PASSWORD = 2005,
            
      [global::ProtoBuf.ProtoEnum(Name=@"ERR_SERVER_FULL", Value=3000)]
      ERR_SERVER_FULL = 3000,
            
      [global::ProtoBuf.ProtoEnum(Name=@"ERR_GAMEPLAY_INVALID_MODE", Value=4000)]
      ERR_GAMEPLAY_INVALID_MODE = 4000
    }
  
    [global::ProtoBuf.ProtoContract(Name=@"RESPONSE_MSG")]
    public enum RESPONSE_MSG
    {
            
      [global::ProtoBuf.ProtoEnum(Name=@"HEART", Value=1000)]
      HEART = 1000,
            
      [global::ProtoBuf.ProtoEnum(Name=@"FLAGS", Value=1001)]
      FLAGS = 1001,
            
      [global::ProtoBuf.ProtoEnum(Name=@"LOGIN", Value=1002)]
      LOGIN = 1002,
            
      [global::ProtoBuf.ProtoEnum(Name=@"WAITING", Value=1003)]
      WAITING = 1003,
            
      [global::ProtoBuf.ProtoEnum(Name=@"READY", Value=1004)]
      READY = 1004,
            
      [global::ProtoBuf.ProtoEnum(Name=@"LIST_GAME", Value=1005)]
      LIST_GAME = 1005,
            
      [global::ProtoBuf.ProtoEnum(Name=@"CREATE_GAME", Value=1006)]
      CREATE_GAME = 1006,
            
      [global::ProtoBuf.ProtoEnum(Name=@"DESTROY_GAME", Value=1007)]
      DESTROY_GAME = 1007,
            
      [global::ProtoBuf.ProtoEnum(Name=@"ENTER_GAME", Value=1008)]
      ENTER_GAME = 1008,
            
      [global::ProtoBuf.ProtoEnum(Name=@"EXIT_GAME", Value=1009)]
      EXIT_GAME = 1009,
            
      [global::ProtoBuf.ProtoEnum(Name=@"SEND_TO_PLAYER", Value=1010)]
      SEND_TO_PLAYER = 1010
    }
  
    [global::ProtoBuf.ProtoContract(Name=@"REQUEST_MSG")]
    public enum REQUEST_MSG
    {
            
      [global::ProtoBuf.ProtoEnum(Name=@"SERVER_STATUS", Value=2000)]
      SERVER_STATUS = 2000
    }
  
}