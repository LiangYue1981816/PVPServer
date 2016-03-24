// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: ProtoGateClient.proto

#ifndef PROTOBUF_ProtoGateClient_2eproto__INCLUDED
#define PROTOBUF_ProtoGateClient_2eproto__INCLUDED

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

namespace ProtoGateClient {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_ProtoGateClient_2eproto();
void protobuf_AssignDesc_ProtoGateClient_2eproto();
void protobuf_ShutdownFile_ProtoGateClient_2eproto();

class Heart;
class Login;
class ListGameServer;
class SendToPlayer;

enum REQUEST_MSG {
  HEART = 3000,
  LOGIN = 3001,
  LIST_GAME_SERVER = 3002,
  SEND_TO_PLAYER = 3003
};
bool REQUEST_MSG_IsValid(int value);
const REQUEST_MSG REQUEST_MSG_MIN = HEART;
const REQUEST_MSG REQUEST_MSG_MAX = SEND_TO_PLAYER;
const int REQUEST_MSG_ARRAYSIZE = REQUEST_MSG_MAX + 1;

const ::google::protobuf::EnumDescriptor* REQUEST_MSG_descriptor();
inline const ::std::string& REQUEST_MSG_Name(REQUEST_MSG value) {
  return ::google::protobuf::internal::NameOfEnum(
    REQUEST_MSG_descriptor(), value);
}
inline bool REQUEST_MSG_Parse(
    const ::std::string& name, REQUEST_MSG* value) {
  return ::google::protobuf::internal::ParseNamedEnum<REQUEST_MSG>(
    REQUEST_MSG_descriptor(), name, value);
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

  // @@protoc_insertion_point(class_scope:ProtoGateClient.Heart)
 private:
  inline void set_has_timestamp();
  inline void clear_has_timestamp();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::int32 timestamp_;
  friend void  protobuf_AddDesc_ProtoGateClient_2eproto();
  friend void protobuf_AssignDesc_ProtoGateClient_2eproto();
  friend void protobuf_ShutdownFile_ProtoGateClient_2eproto();

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

  // required uint32 guid = 1;
  inline bool has_guid() const;
  inline void clear_guid();
  static const int kGuidFieldNumber = 1;
  inline ::google::protobuf::uint32 guid() const;
  inline void set_guid(::google::protobuf::uint32 value);

  // required int32 version = 2;
  inline bool has_version() const;
  inline void clear_version();
  static const int kVersionFieldNumber = 2;
  inline ::google::protobuf::int32 version() const;
  inline void set_version(::google::protobuf::int32 value);

  // @@protoc_insertion_point(class_scope:ProtoGateClient.Login)
 private:
  inline void set_has_guid();
  inline void clear_has_guid();
  inline void set_has_version();
  inline void clear_has_version();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::uint32 guid_;
  ::google::protobuf::int32 version_;
  friend void  protobuf_AddDesc_ProtoGateClient_2eproto();
  friend void protobuf_AssignDesc_ProtoGateClient_2eproto();
  friend void protobuf_ShutdownFile_ProtoGateClient_2eproto();

  void InitAsDefaultInstance();
  static Login* default_instance_;
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

  // accessors -------------------------------------------------------

  // @@protoc_insertion_point(class_scope:ProtoGateClient.ListGameServer)
 private:

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  friend void  protobuf_AddDesc_ProtoGateClient_2eproto();
  friend void protobuf_AssignDesc_ProtoGateClient_2eproto();
  friend void protobuf_ShutdownFile_ProtoGateClient_2eproto();

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

  // required uint32 guid = 1;
  inline bool has_guid() const;
  inline void clear_guid();
  static const int kGuidFieldNumber = 1;
  inline ::google::protobuf::uint32 guid() const;
  inline void set_guid(::google::protobuf::uint32 value);

  // required int32 size = 2;
  inline bool has_size() const;
  inline void clear_size();
  static const int kSizeFieldNumber = 2;
  inline ::google::protobuf::int32 size() const;
  inline void set_size(::google::protobuf::int32 value);

  // required bytes data = 3;
  inline bool has_data() const;
  inline void clear_data();
  static const int kDataFieldNumber = 3;
  inline const ::std::string& data() const;
  inline void set_data(const ::std::string& value);
  inline void set_data(const char* value);
  inline void set_data(const void* value, size_t size);
  inline ::std::string* mutable_data();
  inline ::std::string* release_data();
  inline void set_allocated_data(::std::string* data);

  // repeated int32 players = 4;
  inline int players_size() const;
  inline void clear_players();
  static const int kPlayersFieldNumber = 4;
  inline ::google::protobuf::int32 players(int index) const;
  inline void set_players(int index, ::google::protobuf::int32 value);
  inline void add_players(::google::protobuf::int32 value);
  inline const ::google::protobuf::RepeatedField< ::google::protobuf::int32 >&
      players() const;
  inline ::google::protobuf::RepeatedField< ::google::protobuf::int32 >*
      mutable_players();

  // @@protoc_insertion_point(class_scope:ProtoGateClient.SendToPlayer)
 private:
  inline void set_has_guid();
  inline void clear_has_guid();
  inline void set_has_size();
  inline void clear_has_size();
  inline void set_has_data();
  inline void clear_has_data();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::uint32 guid_;
  ::google::protobuf::int32 size_;
  ::std::string* data_;
  ::google::protobuf::RepeatedField< ::google::protobuf::int32 > players_;
  friend void  protobuf_AddDesc_ProtoGateClient_2eproto();
  friend void protobuf_AssignDesc_ProtoGateClient_2eproto();
  friend void protobuf_ShutdownFile_ProtoGateClient_2eproto();

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
  // @@protoc_insertion_point(field_get:ProtoGateClient.Heart.timestamp)
  return timestamp_;
}
inline void Heart::set_timestamp(::google::protobuf::int32 value) {
  set_has_timestamp();
  timestamp_ = value;
  // @@protoc_insertion_point(field_set:ProtoGateClient.Heart.timestamp)
}

// -------------------------------------------------------------------

// Login

// required uint32 guid = 1;
inline bool Login::has_guid() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void Login::set_has_guid() {
  _has_bits_[0] |= 0x00000001u;
}
inline void Login::clear_has_guid() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void Login::clear_guid() {
  guid_ = 0u;
  clear_has_guid();
}
inline ::google::protobuf::uint32 Login::guid() const {
  // @@protoc_insertion_point(field_get:ProtoGateClient.Login.guid)
  return guid_;
}
inline void Login::set_guid(::google::protobuf::uint32 value) {
  set_has_guid();
  guid_ = value;
  // @@protoc_insertion_point(field_set:ProtoGateClient.Login.guid)
}

// required int32 version = 2;
inline bool Login::has_version() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void Login::set_has_version() {
  _has_bits_[0] |= 0x00000002u;
}
inline void Login::clear_has_version() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void Login::clear_version() {
  version_ = 0;
  clear_has_version();
}
inline ::google::protobuf::int32 Login::version() const {
  // @@protoc_insertion_point(field_get:ProtoGateClient.Login.version)
  return version_;
}
inline void Login::set_version(::google::protobuf::int32 value) {
  set_has_version();
  version_ = value;
  // @@protoc_insertion_point(field_set:ProtoGateClient.Login.version)
}

// -------------------------------------------------------------------

// ListGameServer

// -------------------------------------------------------------------

// SendToPlayer

// required uint32 guid = 1;
inline bool SendToPlayer::has_guid() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void SendToPlayer::set_has_guid() {
  _has_bits_[0] |= 0x00000001u;
}
inline void SendToPlayer::clear_has_guid() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void SendToPlayer::clear_guid() {
  guid_ = 0u;
  clear_has_guid();
}
inline ::google::protobuf::uint32 SendToPlayer::guid() const {
  // @@protoc_insertion_point(field_get:ProtoGateClient.SendToPlayer.guid)
  return guid_;
}
inline void SendToPlayer::set_guid(::google::protobuf::uint32 value) {
  set_has_guid();
  guid_ = value;
  // @@protoc_insertion_point(field_set:ProtoGateClient.SendToPlayer.guid)
}

// required int32 size = 2;
inline bool SendToPlayer::has_size() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void SendToPlayer::set_has_size() {
  _has_bits_[0] |= 0x00000002u;
}
inline void SendToPlayer::clear_has_size() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void SendToPlayer::clear_size() {
  size_ = 0;
  clear_has_size();
}
inline ::google::protobuf::int32 SendToPlayer::size() const {
  // @@protoc_insertion_point(field_get:ProtoGateClient.SendToPlayer.size)
  return size_;
}
inline void SendToPlayer::set_size(::google::protobuf::int32 value) {
  set_has_size();
  size_ = value;
  // @@protoc_insertion_point(field_set:ProtoGateClient.SendToPlayer.size)
}

// required bytes data = 3;
inline bool SendToPlayer::has_data() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void SendToPlayer::set_has_data() {
  _has_bits_[0] |= 0x00000004u;
}
inline void SendToPlayer::clear_has_data() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void SendToPlayer::clear_data() {
  if (data_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    data_->clear();
  }
  clear_has_data();
}
inline const ::std::string& SendToPlayer::data() const {
  // @@protoc_insertion_point(field_get:ProtoGateClient.SendToPlayer.data)
  return *data_;
}
inline void SendToPlayer::set_data(const ::std::string& value) {
  set_has_data();
  if (data_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    data_ = new ::std::string;
  }
  data_->assign(value);
  // @@protoc_insertion_point(field_set:ProtoGateClient.SendToPlayer.data)
}
inline void SendToPlayer::set_data(const char* value) {
  set_has_data();
  if (data_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    data_ = new ::std::string;
  }
  data_->assign(value);
  // @@protoc_insertion_point(field_set_char:ProtoGateClient.SendToPlayer.data)
}
inline void SendToPlayer::set_data(const void* value, size_t size) {
  set_has_data();
  if (data_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    data_ = new ::std::string;
  }
  data_->assign(reinterpret_cast<const char*>(value), size);
  // @@protoc_insertion_point(field_set_pointer:ProtoGateClient.SendToPlayer.data)
}
inline ::std::string* SendToPlayer::mutable_data() {
  set_has_data();
  if (data_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    data_ = new ::std::string;
  }
  // @@protoc_insertion_point(field_mutable:ProtoGateClient.SendToPlayer.data)
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
  // @@protoc_insertion_point(field_set_allocated:ProtoGateClient.SendToPlayer.data)
}

// repeated int32 players = 4;
inline int SendToPlayer::players_size() const {
  return players_.size();
}
inline void SendToPlayer::clear_players() {
  players_.Clear();
}
inline ::google::protobuf::int32 SendToPlayer::players(int index) const {
  // @@protoc_insertion_point(field_get:ProtoGateClient.SendToPlayer.players)
  return players_.Get(index);
}
inline void SendToPlayer::set_players(int index, ::google::protobuf::int32 value) {
  players_.Set(index, value);
  // @@protoc_insertion_point(field_set:ProtoGateClient.SendToPlayer.players)
}
inline void SendToPlayer::add_players(::google::protobuf::int32 value) {
  players_.Add(value);
  // @@protoc_insertion_point(field_add:ProtoGateClient.SendToPlayer.players)
}
inline const ::google::protobuf::RepeatedField< ::google::protobuf::int32 >&
SendToPlayer::players() const {
  // @@protoc_insertion_point(field_list:ProtoGateClient.SendToPlayer.players)
  return players_;
}
inline ::google::protobuf::RepeatedField< ::google::protobuf::int32 >*
SendToPlayer::mutable_players() {
  // @@protoc_insertion_point(field_mutable_list:ProtoGateClient.SendToPlayer.players)
  return &players_;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace ProtoGateClient

#ifndef SWIG
namespace google {
namespace protobuf {

template <> struct is_proto_enum< ::ProtoGateClient::REQUEST_MSG> : ::google::protobuf::internal::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::ProtoGateClient::REQUEST_MSG>() {
  return ::ProtoGateClient::REQUEST_MSG_descriptor();
}

}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_ProtoGateClient_2eproto__INCLUDED
