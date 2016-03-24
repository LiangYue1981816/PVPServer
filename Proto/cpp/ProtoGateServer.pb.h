// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: ProtoGateServer.proto

#ifndef PROTOBUF_ProtoGateServer_2eproto__INCLUDED
#define PROTOBUF_ProtoGateServer_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 2006000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 2006001 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/generated_enum_reflection.h>
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)

namespace ProtoGateServer {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_ProtoGateServer_2eproto();
void protobuf_AssignDesc_ProtoGateServer_2eproto();
void protobuf_ShutdownFile_ProtoGateServer_2eproto();

class Heart;
class Login;
class ListGameServer;
class ListGameServer_GameServer;
class SendToPlayer;

enum VERSION_NUMBER {
  VERSION = 65536
};
bool VERSION_NUMBER_IsValid(int value);
const VERSION_NUMBER VERSION_NUMBER_MIN = VERSION;
const VERSION_NUMBER VERSION_NUMBER_MAX = VERSION;
const int VERSION_NUMBER_ARRAYSIZE = VERSION_NUMBER_MAX + 1;

const ::google::protobuf::EnumDescriptor* VERSION_NUMBER_descriptor();
inline const ::std::string& VERSION_NUMBER_Name(VERSION_NUMBER value) {
  return ::google::protobuf::internal::NameOfEnum(
    VERSION_NUMBER_descriptor(), value);
}
inline bool VERSION_NUMBER_Parse(
    const ::std::string& name, VERSION_NUMBER* value) {
  return ::google::protobuf::internal::ParseNamedEnum<VERSION_NUMBER>(
    VERSION_NUMBER_descriptor(), name, value);
}
enum FLAGS_CODE {
  PLAYER_FLAGS_NONE = 0,
  PLAYER_FLAGS_LOGIN = 1
};
bool FLAGS_CODE_IsValid(int value);
const FLAGS_CODE FLAGS_CODE_MIN = PLAYER_FLAGS_NONE;
const FLAGS_CODE FLAGS_CODE_MAX = PLAYER_FLAGS_LOGIN;
const int FLAGS_CODE_ARRAYSIZE = FLAGS_CODE_MAX + 1;

const ::google::protobuf::EnumDescriptor* FLAGS_CODE_descriptor();
inline const ::std::string& FLAGS_CODE_Name(FLAGS_CODE value) {
  return ::google::protobuf::internal::NameOfEnum(
    FLAGS_CODE_descriptor(), value);
}
inline bool FLAGS_CODE_Parse(
    const ::std::string& name, FLAGS_CODE* value) {
  return ::google::protobuf::internal::ParseNamedEnum<FLAGS_CODE>(
    FLAGS_CODE_descriptor(), name, value);
}
enum ERROR_CODE {
  ERR_NONE = 0,
  ERR_VERSION_INVALID = 1,
  ERR_PLAYER_INVALID = 1000,
  ERR_PLAYER_INVALID_GUID = 1001,
  ERR_PLAYER_FLAGS_NOT_NONE = 1002,
  ERR_PLAYER_FLAGS_NOT_LOGIN = 1003
};
bool ERROR_CODE_IsValid(int value);
const ERROR_CODE ERROR_CODE_MIN = ERR_NONE;
const ERROR_CODE ERROR_CODE_MAX = ERR_PLAYER_FLAGS_NOT_LOGIN;
const int ERROR_CODE_ARRAYSIZE = ERROR_CODE_MAX + 1;

const ::google::protobuf::EnumDescriptor* ERROR_CODE_descriptor();
inline const ::std::string& ERROR_CODE_Name(ERROR_CODE value) {
  return ::google::protobuf::internal::NameOfEnum(
    ERROR_CODE_descriptor(), value);
}
inline bool ERROR_CODE_Parse(
    const ::std::string& name, ERROR_CODE* value) {
  return ::google::protobuf::internal::ParseNamedEnum<ERROR_CODE>(
    ERROR_CODE_descriptor(), name, value);
}
enum RESPONSE_MSG {
  HEART = 3000,
  LOGIN = 3001,
  LIST_GAME_SERVER = 3002,
  SEND_TO_PLAYER = 3003
};
bool RESPONSE_MSG_IsValid(int value);
const RESPONSE_MSG RESPONSE_MSG_MIN = HEART;
const RESPONSE_MSG RESPONSE_MSG_MAX = SEND_TO_PLAYER;
const int RESPONSE_MSG_ARRAYSIZE = RESPONSE_MSG_MAX + 1;

const ::google::protobuf::EnumDescriptor* RESPONSE_MSG_descriptor();
inline const ::std::string& RESPONSE_MSG_Name(RESPONSE_MSG value) {
  return ::google::protobuf::internal::NameOfEnum(
    RESPONSE_MSG_descriptor(), value);
}
inline bool RESPONSE_MSG_Parse(
    const ::std::string& name, RESPONSE_MSG* value) {
  return ::google::protobuf::internal::ParseNamedEnum<RESPONSE_MSG>(
    RESPONSE_MSG_descriptor(), name, value);
}
// ===================================================================

class Heart : public ::google::protobuf::Message {
 public:
  Heart();
  virtual ~Heart();

  Heart(const Heart& from);

  inline Heart& operator=(const Heart& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const Heart& default_instance();

  void Swap(Heart* other);

  // implements Message ----------------------------------------------

  Heart* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const Heart& from);
  void MergeFrom(const Heart& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:
  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // required int32 timestamp = 1;
  inline bool has_timestamp() const;
  inline void clear_timestamp();
  static const int kTimestampFieldNumber = 1;
  inline ::google::protobuf::int32 timestamp() const;
  inline void set_timestamp(::google::protobuf::int32 value);

  // @@protoc_insertion_point(class_scope:ProtoGateServer.Heart)
 private:
  inline void set_has_timestamp();
  inline void clear_has_timestamp();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::int32 timestamp_;
  friend void  protobuf_AddDesc_ProtoGateServer_2eproto();
  friend void protobuf_AssignDesc_ProtoGateServer_2eproto();
  friend void protobuf_ShutdownFile_ProtoGateServer_2eproto();

  void InitAsDefaultInstance();
  static Heart* default_instance_;
};
// -------------------------------------------------------------------

class Login : public ::google::protobuf::Message {
 public:
  Login();
  virtual ~Login();

  Login(const Login& from);

  inline Login& operator=(const Login& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const Login& default_instance();

  void Swap(Login* other);

  // implements Message ----------------------------------------------

  Login* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const Login& from);
  void MergeFrom(const Login& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:
  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // required .ProtoGateServer.ERROR_CODE err = 1;
  inline bool has_err() const;
  inline void clear_err();
  static const int kErrFieldNumber = 1;
  inline ::ProtoGateServer::ERROR_CODE err() const;
  inline void set_err(::ProtoGateServer::ERROR_CODE value);

  // optional uint32 guid = 2;
  inline bool has_guid() const;
  inline void clear_guid();
  static const int kGuidFieldNumber = 2;
  inline ::google::protobuf::uint32 guid() const;
  inline void set_guid(::google::protobuf::uint32 value);

  // @@protoc_insertion_point(class_scope:ProtoGateServer.Login)
 private:
  inline void set_has_err();
  inline void clear_has_err();
  inline void set_has_guid();
  inline void clear_has_guid();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  int err_;
  ::google::protobuf::uint32 guid_;
  friend void  protobuf_AddDesc_ProtoGateServer_2eproto();
  friend void protobuf_AssignDesc_ProtoGateServer_2eproto();
  friend void protobuf_ShutdownFile_ProtoGateServer_2eproto();

  void InitAsDefaultInstance();
  static Login* default_instance_;
};
// -------------------------------------------------------------------

class ListGameServer_GameServer : public ::google::protobuf::Message {
 public:
  ListGameServer_GameServer();
  virtual ~ListGameServer_GameServer();

  ListGameServer_GameServer(const ListGameServer_GameServer& from);

  inline ListGameServer_GameServer& operator=(const ListGameServer_GameServer& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const ListGameServer_GameServer& default_instance();

  void Swap(ListGameServer_GameServer* other);

  // implements Message ----------------------------------------------

  ListGameServer_GameServer* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const ListGameServer_GameServer& from);
  void MergeFrom(const ListGameServer_GameServer& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:
  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // required string ip = 1;
  inline bool has_ip() const;
  inline void clear_ip();
  static const int kIpFieldNumber = 1;
  inline const ::std::string& ip() const;
  inline void set_ip(const ::std::string& value);
  inline void set_ip(const char* value);
  inline void set_ip(const char* value, size_t size);
  inline ::std::string* mutable_ip();
  inline ::std::string* release_ip();
  inline void set_allocated_ip(::std::string* ip);

  // required int32 port = 2;
  inline bool has_port() const;
  inline void clear_port();
  static const int kPortFieldNumber = 2;
  inline ::google::protobuf::int32 port() const;
  inline void set_port(::google::protobuf::int32 value);

  // required int32 maxGames = 3;
  inline bool has_maxgames() const;
  inline void clear_maxgames();
  static const int kMaxGamesFieldNumber = 3;
  inline ::google::protobuf::int32 maxgames() const;
  inline void set_maxgames(::google::protobuf::int32 value);

  // required int32 curGames = 4;
  inline bool has_curgames() const;
  inline void clear_curgames();
  static const int kCurGamesFieldNumber = 4;
  inline ::google::protobuf::int32 curgames() const;
  inline void set_curgames(::google::protobuf::int32 value);

  // @@protoc_insertion_point(class_scope:ProtoGateServer.ListGameServer.GameServer)
 private:
  inline void set_has_ip();
  inline void clear_has_ip();
  inline void set_has_port();
  inline void clear_has_port();
  inline void set_has_maxgames();
  inline void clear_has_maxgames();
  inline void set_has_curgames();
  inline void clear_has_curgames();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::std::string* ip_;
  ::google::protobuf::int32 port_;
  ::google::protobuf::int32 maxgames_;
  ::google::protobuf::int32 curgames_;
  friend void  protobuf_AddDesc_ProtoGateServer_2eproto();
  friend void protobuf_AssignDesc_ProtoGateServer_2eproto();
  friend void protobuf_ShutdownFile_ProtoGateServer_2eproto();

  void InitAsDefaultInstance();
  static ListGameServer_GameServer* default_instance_;
};
// -------------------------------------------------------------------

class ListGameServer : public ::google::protobuf::Message {
 public:
  ListGameServer();
  virtual ~ListGameServer();

  ListGameServer(const ListGameServer& from);

  inline ListGameServer& operator=(const ListGameServer& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const ListGameServer& default_instance();

  void Swap(ListGameServer* other);

  // implements Message ----------------------------------------------

  ListGameServer* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const ListGameServer& from);
  void MergeFrom(const ListGameServer& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:
  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  typedef ListGameServer_GameServer GameServer;

  // accessors -------------------------------------------------------

  // repeated .ProtoGateServer.ListGameServer.GameServer servers = 1;
  inline int servers_size() const;
  inline void clear_servers();
  static const int kServersFieldNumber = 1;
  inline const ::ProtoGateServer::ListGameServer_GameServer& servers(int index) const;
  inline ::ProtoGateServer::ListGameServer_GameServer* mutable_servers(int index);
  inline ::ProtoGateServer::ListGameServer_GameServer* add_servers();
  inline const ::google::protobuf::RepeatedPtrField< ::ProtoGateServer::ListGameServer_GameServer >&
      servers() const;
  inline ::google::protobuf::RepeatedPtrField< ::ProtoGateServer::ListGameServer_GameServer >*
      mutable_servers();

  // @@protoc_insertion_point(class_scope:ProtoGateServer.ListGameServer)
 private:

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::RepeatedPtrField< ::ProtoGateServer::ListGameServer_GameServer > servers_;
  friend void  protobuf_AddDesc_ProtoGateServer_2eproto();
  friend void protobuf_AssignDesc_ProtoGateServer_2eproto();
  friend void protobuf_ShutdownFile_ProtoGateServer_2eproto();

  void InitAsDefaultInstance();
  static ListGameServer* default_instance_;
};
// -------------------------------------------------------------------

class SendToPlayer : public ::google::protobuf::Message {
 public:
  SendToPlayer();
  virtual ~SendToPlayer();

  SendToPlayer(const SendToPlayer& from);

  inline SendToPlayer& operator=(const SendToPlayer& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const SendToPlayer& default_instance();

  void Swap(SendToPlayer* other);

  // implements Message ----------------------------------------------

  SendToPlayer* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const SendToPlayer& from);
  void MergeFrom(const SendToPlayer& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:
  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // required int32 size = 1;
  inline bool has_size() const;
  inline void clear_size();
  static const int kSizeFieldNumber = 1;
  inline ::google::protobuf::int32 size() const;
  inline void set_size(::google::protobuf::int32 value);

  // required bytes data = 2;
  inline bool has_data() const;
  inline void clear_data();
  static const int kDataFieldNumber = 2;
  inline const ::std::string& data() const;
  inline void set_data(const ::std::string& value);
  inline void set_data(const char* value);
  inline void set_data(const void* value, size_t size);
  inline ::std::string* mutable_data();
  inline ::std::string* release_data();
  inline void set_allocated_data(::std::string* data);

  // @@protoc_insertion_point(class_scope:ProtoGateServer.SendToPlayer)
 private:
  inline void set_has_size();
  inline void clear_has_size();
  inline void set_has_data();
  inline void clear_has_data();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::std::string* data_;
  ::google::protobuf::int32 size_;
  friend void  protobuf_AddDesc_ProtoGateServer_2eproto();
  friend void protobuf_AssignDesc_ProtoGateServer_2eproto();
  friend void protobuf_ShutdownFile_ProtoGateServer_2eproto();

  void InitAsDefaultInstance();
  static SendToPlayer* default_instance_;
};
// ===================================================================


// ===================================================================

// Heart

// required int32 timestamp = 1;
inline bool Heart::has_timestamp() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void Heart::set_has_timestamp() {
  _has_bits_[0] |= 0x00000001u;
}
inline void Heart::clear_has_timestamp() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void Heart::clear_timestamp() {
  timestamp_ = 0;
  clear_has_timestamp();
}
inline ::google::protobuf::int32 Heart::timestamp() const {
  // @@protoc_insertion_point(field_get:ProtoGateServer.Heart.timestamp)
  return timestamp_;
}
inline void Heart::set_timestamp(::google::protobuf::int32 value) {
  set_has_timestamp();
  timestamp_ = value;
  // @@protoc_insertion_point(field_set:ProtoGateServer.Heart.timestamp)
}

// -------------------------------------------------------------------

// Login

// required .ProtoGateServer.ERROR_CODE err = 1;
inline bool Login::has_err() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void Login::set_has_err() {
  _has_bits_[0] |= 0x00000001u;
}
inline void Login::clear_has_err() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void Login::clear_err() {
  err_ = 0;
  clear_has_err();
}
inline ::ProtoGateServer::ERROR_CODE Login::err() const {
  // @@protoc_insertion_point(field_get:ProtoGateServer.Login.err)
  return static_cast< ::ProtoGateServer::ERROR_CODE >(err_);
}
inline void Login::set_err(::ProtoGateServer::ERROR_CODE value) {
  assert(::ProtoGateServer::ERROR_CODE_IsValid(value));
  set_has_err();
  err_ = value;
  // @@protoc_insertion_point(field_set:ProtoGateServer.Login.err)
}

// optional uint32 guid = 2;
inline bool Login::has_guid() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void Login::set_has_guid() {
  _has_bits_[0] |= 0x00000002u;
}
inline void Login::clear_has_guid() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void Login::clear_guid() {
  guid_ = 0u;
  clear_has_guid();
}
inline ::google::protobuf::uint32 Login::guid() const {
  // @@protoc_insertion_point(field_get:ProtoGateServer.Login.guid)
  return guid_;
}
inline void Login::set_guid(::google::protobuf::uint32 value) {
  set_has_guid();
  guid_ = value;
  // @@protoc_insertion_point(field_set:ProtoGateServer.Login.guid)
}

// -------------------------------------------------------------------

// ListGameServer_GameServer

// required string ip = 1;
inline bool ListGameServer_GameServer::has_ip() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void ListGameServer_GameServer::set_has_ip() {
  _has_bits_[0] |= 0x00000001u;
}
inline void ListGameServer_GameServer::clear_has_ip() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void ListGameServer_GameServer::clear_ip() {
  if (ip_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    ip_->clear();
  }
  clear_has_ip();
}
inline const ::std::string& ListGameServer_GameServer::ip() const {
  // @@protoc_insertion_point(field_get:ProtoGateServer.ListGameServer.GameServer.ip)
  return *ip_;
}
inline void ListGameServer_GameServer::set_ip(const ::std::string& value) {
  set_has_ip();
  if (ip_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    ip_ = new ::std::string;
  }
  ip_->assign(value);
  // @@protoc_insertion_point(field_set:ProtoGateServer.ListGameServer.GameServer.ip)
}
inline void ListGameServer_GameServer::set_ip(const char* value) {
  set_has_ip();
  if (ip_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    ip_ = new ::std::string;
  }
  ip_->assign(value);
  // @@protoc_insertion_point(field_set_char:ProtoGateServer.ListGameServer.GameServer.ip)
}
inline void ListGameServer_GameServer::set_ip(const char* value, size_t size) {
  set_has_ip();
  if (ip_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    ip_ = new ::std::string;
  }
  ip_->assign(reinterpret_cast<const char*>(value), size);
  // @@protoc_insertion_point(field_set_pointer:ProtoGateServer.ListGameServer.GameServer.ip)
}
inline ::std::string* ListGameServer_GameServer::mutable_ip() {
  set_has_ip();
  if (ip_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    ip_ = new ::std::string;
  }
  // @@protoc_insertion_point(field_mutable:ProtoGateServer.ListGameServer.GameServer.ip)
  return ip_;
}
inline ::std::string* ListGameServer_GameServer::release_ip() {
  clear_has_ip();
  if (ip_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    return NULL;
  } else {
    ::std::string* temp = ip_;
    ip_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    return temp;
  }
}
inline void ListGameServer_GameServer::set_allocated_ip(::std::string* ip) {
  if (ip_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete ip_;
  }
  if (ip) {
    set_has_ip();
    ip_ = ip;
  } else {
    clear_has_ip();
    ip_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  }
  // @@protoc_insertion_point(field_set_allocated:ProtoGateServer.ListGameServer.GameServer.ip)
}

// required int32 port = 2;
inline bool ListGameServer_GameServer::has_port() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void ListGameServer_GameServer::set_has_port() {
  _has_bits_[0] |= 0x00000002u;
}
inline void ListGameServer_GameServer::clear_has_port() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void ListGameServer_GameServer::clear_port() {
  port_ = 0;
  clear_has_port();
}
inline ::google::protobuf::int32 ListGameServer_GameServer::port() const {
  // @@protoc_insertion_point(field_get:ProtoGateServer.ListGameServer.GameServer.port)
  return port_;
}
inline void ListGameServer_GameServer::set_port(::google::protobuf::int32 value) {
  set_has_port();
  port_ = value;
  // @@protoc_insertion_point(field_set:ProtoGateServer.ListGameServer.GameServer.port)
}

// required int32 maxGames = 3;
inline bool ListGameServer_GameServer::has_maxgames() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void ListGameServer_GameServer::set_has_maxgames() {
  _has_bits_[0] |= 0x00000004u;
}
inline void ListGameServer_GameServer::clear_has_maxgames() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void ListGameServer_GameServer::clear_maxgames() {
  maxgames_ = 0;
  clear_has_maxgames();
}
inline ::google::protobuf::int32 ListGameServer_GameServer::maxgames() const {
  // @@protoc_insertion_point(field_get:ProtoGateServer.ListGameServer.GameServer.maxGames)
  return maxgames_;
}
inline void ListGameServer_GameServer::set_maxgames(::google::protobuf::int32 value) {
  set_has_maxgames();
  maxgames_ = value;
  // @@protoc_insertion_point(field_set:ProtoGateServer.ListGameServer.GameServer.maxGames)
}

// required int32 curGames = 4;
inline bool ListGameServer_GameServer::has_curgames() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void ListGameServer_GameServer::set_has_curgames() {
  _has_bits_[0] |= 0x00000008u;
}
inline void ListGameServer_GameServer::clear_has_curgames() {
  _has_bits_[0] &= ~0x00000008u;
}
inline void ListGameServer_GameServer::clear_curgames() {
  curgames_ = 0;
  clear_has_curgames();
}
inline ::google::protobuf::int32 ListGameServer_GameServer::curgames() const {
  // @@protoc_insertion_point(field_get:ProtoGateServer.ListGameServer.GameServer.curGames)
  return curgames_;
}
inline void ListGameServer_GameServer::set_curgames(::google::protobuf::int32 value) {
  set_has_curgames();
  curgames_ = value;
  // @@protoc_insertion_point(field_set:ProtoGateServer.ListGameServer.GameServer.curGames)
}

// -------------------------------------------------------------------

// ListGameServer

// repeated .ProtoGateServer.ListGameServer.GameServer servers = 1;
inline int ListGameServer::servers_size() const {
  return servers_.size();
}
inline void ListGameServer::clear_servers() {
  servers_.Clear();
}
inline const ::ProtoGateServer::ListGameServer_GameServer& ListGameServer::servers(int index) const {
  // @@protoc_insertion_point(field_get:ProtoGateServer.ListGameServer.servers)
  return servers_.Get(index);
}
inline ::ProtoGateServer::ListGameServer_GameServer* ListGameServer::mutable_servers(int index) {
  // @@protoc_insertion_point(field_mutable:ProtoGateServer.ListGameServer.servers)
  return servers_.Mutable(index);
}
inline ::ProtoGateServer::ListGameServer_GameServer* ListGameServer::add_servers() {
  // @@protoc_insertion_point(field_add:ProtoGateServer.ListGameServer.servers)
  return servers_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::ProtoGateServer::ListGameServer_GameServer >&
ListGameServer::servers() const {
  // @@protoc_insertion_point(field_list:ProtoGateServer.ListGameServer.servers)
  return servers_;
}
inline ::google::protobuf::RepeatedPtrField< ::ProtoGateServer::ListGameServer_GameServer >*
ListGameServer::mutable_servers() {
  // @@protoc_insertion_point(field_mutable_list:ProtoGateServer.ListGameServer.servers)
  return &servers_;
}

// -------------------------------------------------------------------

// SendToPlayer

// required int32 size = 1;
inline bool SendToPlayer::has_size() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void SendToPlayer::set_has_size() {
  _has_bits_[0] |= 0x00000001u;
}
inline void SendToPlayer::clear_has_size() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void SendToPlayer::clear_size() {
  size_ = 0;
  clear_has_size();
}
inline ::google::protobuf::int32 SendToPlayer::size() const {
  // @@protoc_insertion_point(field_get:ProtoGateServer.SendToPlayer.size)
  return size_;
}
inline void SendToPlayer::set_size(::google::protobuf::int32 value) {
  set_has_size();
  size_ = value;
  // @@protoc_insertion_point(field_set:ProtoGateServer.SendToPlayer.size)
}

// required bytes data = 2;
inline bool SendToPlayer::has_data() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void SendToPlayer::set_has_data() {
  _has_bits_[0] |= 0x00000002u;
}
inline void SendToPlayer::clear_has_data() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void SendToPlayer::clear_data() {
  if (data_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    data_->clear();
  }
  clear_has_data();
}
inline const ::std::string& SendToPlayer::data() const {
  // @@protoc_insertion_point(field_get:ProtoGateServer.SendToPlayer.data)
  return *data_;
}
inline void SendToPlayer::set_data(const ::std::string& value) {
  set_has_data();
  if (data_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    data_ = new ::std::string;
  }
  data_->assign(value);
  // @@protoc_insertion_point(field_set:ProtoGateServer.SendToPlayer.data)
}
inline void SendToPlayer::set_data(const char* value) {
  set_has_data();
  if (data_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    data_ = new ::std::string;
  }
  data_->assign(value);
  // @@protoc_insertion_point(field_set_char:ProtoGateServer.SendToPlayer.data)
}
inline void SendToPlayer::set_data(const void* value, size_t size) {
  set_has_data();
  if (data_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    data_ = new ::std::string;
  }
  data_->assign(reinterpret_cast<const char*>(value), size);
  // @@protoc_insertion_point(field_set_pointer:ProtoGateServer.SendToPlayer.data)
}
inline ::std::string* SendToPlayer::mutable_data() {
  set_has_data();
  if (data_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    data_ = new ::std::string;
  }
  // @@protoc_insertion_point(field_mutable:ProtoGateServer.SendToPlayer.data)
  return data_;
}
inline ::std::string* SendToPlayer::release_data() {
  clear_has_data();
  if (data_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    return NULL;
  } else {
    ::std::string* temp = data_;
    data_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    return temp;
  }
}
inline void SendToPlayer::set_allocated_data(::std::string* data) {
  if (data_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete data_;
  }
  if (data) {
    set_has_data();
    data_ = data;
  } else {
    clear_has_data();
    data_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  }
  // @@protoc_insertion_point(field_set_allocated:ProtoGateServer.SendToPlayer.data)
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace ProtoGateServer

#ifndef SWIG
namespace google {
namespace protobuf {

template <> struct is_proto_enum< ::ProtoGateServer::VERSION_NUMBER> : ::google::protobuf::internal::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::ProtoGateServer::VERSION_NUMBER>() {
  return ::ProtoGateServer::VERSION_NUMBER_descriptor();
}
template <> struct is_proto_enum< ::ProtoGateServer::FLAGS_CODE> : ::google::protobuf::internal::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::ProtoGateServer::FLAGS_CODE>() {
  return ::ProtoGateServer::FLAGS_CODE_descriptor();
}
template <> struct is_proto_enum< ::ProtoGateServer::ERROR_CODE> : ::google::protobuf::internal::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::ProtoGateServer::ERROR_CODE>() {
  return ::ProtoGateServer::ERROR_CODE_descriptor();
}
template <> struct is_proto_enum< ::ProtoGateServer::RESPONSE_MSG> : ::google::protobuf::internal::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::ProtoGateServer::RESPONSE_MSG>() {
  return ::ProtoGateServer::RESPONSE_MSG_descriptor();
}

}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_ProtoGateServer_2eproto__INCLUDED
