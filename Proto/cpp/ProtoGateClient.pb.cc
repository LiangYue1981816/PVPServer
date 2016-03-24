// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: ProtoGateClient.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "ProtoGateClient.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace ProtoGateClient {

namespace {

const ::google::protobuf::Descriptor* Heart_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  Heart_reflection_ = NULL;
const ::google::protobuf::Descriptor* Login_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  Login_reflection_ = NULL;
const ::google::protobuf::Descriptor* ListGameServer_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  ListGameServer_reflection_ = NULL;
const ::google::protobuf::Descriptor* SendToPlayer_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  SendToPlayer_reflection_ = NULL;
const ::google::protobuf::EnumDescriptor* REQUEST_MSG_descriptor_ = NULL;

}  // namespace


void protobuf_AssignDesc_ProtoGateClient_2eproto() {
  protobuf_AddDesc_ProtoGateClient_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "ProtoGateClient.proto");
  GOOGLE_CHECK(file != NULL);
  Heart_descriptor_ = file->message_type(0);
  static const int Heart_offsets_[1] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Heart, timestamp_),
  };
  Heart_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      Heart_descriptor_,
      Heart::default_instance_,
      Heart_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Heart, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Heart, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(Heart));
  Login_descriptor_ = file->message_type(1);
  static const int Login_offsets_[2] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Login, guid_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Login, version_),
  };
  Login_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      Login_descriptor_,
      Login::default_instance_,
      Login_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Login, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Login, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(Login));
  ListGameServer_descriptor_ = file->message_type(2);
  static const int ListGameServer_offsets_[1] = {
  };
  ListGameServer_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      ListGameServer_descriptor_,
      ListGameServer::default_instance_,
      ListGameServer_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ListGameServer, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ListGameServer, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(ListGameServer));
  SendToPlayer_descriptor_ = file->message_type(3);
  static const int SendToPlayer_offsets_[4] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(SendToPlayer, guid_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(SendToPlayer, size_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(SendToPlayer, data_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(SendToPlayer, players_),
  };
  SendToPlayer_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      SendToPlayer_descriptor_,
      SendToPlayer::default_instance_,
      SendToPlayer_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(SendToPlayer, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(SendToPlayer, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(SendToPlayer));
  REQUEST_MSG_descriptor_ = file->enum_type(0);
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_ProtoGateClient_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    Heart_descriptor_, &Heart::default_instance());
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    Login_descriptor_, &Login::default_instance());
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    ListGameServer_descriptor_, &ListGameServer::default_instance());
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    SendToPlayer_descriptor_, &SendToPlayer::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_ProtoGateClient_2eproto() {
  delete Heart::default_instance_;
  delete Heart_reflection_;
  delete Login::default_instance_;
  delete Login_reflection_;
  delete ListGameServer::default_instance_;
  delete ListGameServer_reflection_;
  delete SendToPlayer::default_instance_;
  delete SendToPlayer_reflection_;
}

void protobuf_AddDesc_ProtoGateClient_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\025ProtoGateClient.proto\022\017ProtoGateClient"
    "\"\032\n\005Heart\022\021\n\ttimestamp\030\001 \002(\005\"&\n\005Login\022\014\n"
    "\004guid\030\001 \002(\r\022\017\n\007version\030\002 \002(\005\"\020\n\016ListGame"
    "Server\"I\n\014SendToPlayer\022\014\n\004guid\030\001 \002(\r\022\014\n\004"
    "size\030\002 \002(\005\022\014\n\004data\030\003 \002(\014\022\017\n\007players\030\004 \003("
    "\005*Q\n\013REQUEST_MSG\022\n\n\005HEART\020\270\027\022\n\n\005LOGIN\020\271\027"
    "\022\025\n\020LIST_GAME_SERVER\020\272\027\022\023\n\016SEND_TO_PLAYE"
    "R\020\273\027B\002H\001", 288);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "ProtoGateClient.proto", &protobuf_RegisterTypes);
  Heart::default_instance_ = new Heart();
  Login::default_instance_ = new Login();
  ListGameServer::default_instance_ = new ListGameServer();
  SendToPlayer::default_instance_ = new SendToPlayer();
  Heart::default_instance_->InitAsDefaultInstance();
  Login::default_instance_->InitAsDefaultInstance();
  ListGameServer::default_instance_->InitAsDefaultInstance();
  SendToPlayer::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_ProtoGateClient_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_ProtoGateClient_2eproto {
  StaticDescriptorInitializer_ProtoGateClient_2eproto() {
    protobuf_AddDesc_ProtoGateClient_2eproto();
  }
} static_descriptor_initializer_ProtoGateClient_2eproto_;
const ::google::protobuf::EnumDescriptor* REQUEST_MSG_descriptor() {
  protobuf_AssignDescriptorsOnce();
  return REQUEST_MSG_descriptor_;
}
bool REQUEST_MSG_IsValid(int value) {
  switch(value) {
    case 3000:
    case 3001:
    case 3002:
    case 3003:
      return true;
    default:
      return false;
  }
}


// ===================================================================

#ifndef _MSC_VER
const int Heart::kTimestampFieldNumber;
#endif  // !_MSC_VER

Heart::Heart()
  : ::google::protobuf::Message() {
  SharedCtor();
  // @@protoc_insertion_point(constructor:ProtoGateClient.Heart)
}

void Heart::InitAsDefaultInstance() {
}

Heart::Heart(const Heart& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:ProtoGateClient.Heart)
}

void Heart::SharedCtor() {
  _cached_size_ = 0;
  timestamp_ = 0;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

Heart::~Heart() {
  // @@protoc_insertion_point(destructor:ProtoGateClient.Heart)
  SharedDtor();
}

void Heart::SharedDtor() {
  if (this != default_instance_) {
  }
}

void Heart::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* Heart::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return Heart_descriptor_;
}

const Heart& Heart::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_ProtoGateClient_2eproto();
  return *default_instance_;
}

Heart* Heart::default_instance_ = NULL;

Heart* Heart::New() const {
  return new Heart;
}

void Heart::Clear() {
  timestamp_ = 0;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool Heart::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:ProtoGateClient.Heart)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required int32 timestamp = 1;
      case 1: {
        if (tag == 8) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &timestamp_)));
          set_has_timestamp();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectAtEnd()) goto success;
        break;
      }

      default: {
      handle_unusual:
        if (tag == 0 ||
            ::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          goto success;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, mutable_unknown_fields()));
        break;
      }
    }
  }
success:
  // @@protoc_insertion_point(parse_success:ProtoGateClient.Heart)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:ProtoGateClient.Heart)
  return false;
#undef DO_
}

void Heart::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:ProtoGateClient.Heart)
  // required int32 timestamp = 1;
  if (has_timestamp()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(1, this->timestamp(), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:ProtoGateClient.Heart)
}

::google::protobuf::uint8* Heart::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:ProtoGateClient.Heart)
  // required int32 timestamp = 1;
  if (has_timestamp()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(1, this->timestamp(), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:ProtoGateClient.Heart)
  return target;
}

int Heart::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // required int32 timestamp = 1;
    if (has_timestamp()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->timestamp());
    }

  }
  if (!unknown_fields().empty()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        unknown_fields());
  }
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void Heart::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const Heart* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const Heart*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void Heart::MergeFrom(const Heart& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_timestamp()) {
      set_timestamp(from.timestamp());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void Heart::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void Heart::CopyFrom(const Heart& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Heart::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000001) != 0x00000001) return false;

  return true;
}

void Heart::Swap(Heart* other) {
  if (other != this) {
    std::swap(timestamp_, other->timestamp_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata Heart::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = Heart_descriptor_;
  metadata.reflection = Heart_reflection_;
  return metadata;
}


// ===================================================================

#ifndef _MSC_VER
const int Login::kGuidFieldNumber;
const int Login::kVersionFieldNumber;
#endif  // !_MSC_VER

Login::Login()
  : ::google::protobuf::Message() {
  SharedCtor();
  // @@protoc_insertion_point(constructor:ProtoGateClient.Login)
}

void Login::InitAsDefaultInstance() {
}

Login::Login(const Login& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:ProtoGateClient.Login)
}

void Login::SharedCtor() {
  _cached_size_ = 0;
  guid_ = 0u;
  version_ = 0;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

Login::~Login() {
  // @@protoc_insertion_point(destructor:ProtoGateClient.Login)
  SharedDtor();
}

void Login::SharedDtor() {
  if (this != default_instance_) {
  }
}

void Login::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* Login::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return Login_descriptor_;
}

const Login& Login::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_ProtoGateClient_2eproto();
  return *default_instance_;
}

Login* Login::default_instance_ = NULL;

Login* Login::New() const {
  return new Login;
}

void Login::Clear() {
#define OFFSET_OF_FIELD_(f) (reinterpret_cast<char*>(      \
  &reinterpret_cast<Login*>(16)->f) - \
   reinterpret_cast<char*>(16))

#define ZR_(first, last) do {                              \
    size_t f = OFFSET_OF_FIELD_(first);                    \
    size_t n = OFFSET_OF_FIELD_(last) - f + sizeof(last);  \
    ::memset(&first, 0, n);                                \
  } while (0)

  ZR_(guid_, version_);

#undef OFFSET_OF_FIELD_
#undef ZR_

  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool Login::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:ProtoGateClient.Login)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required uint32 guid = 1;
      case 1: {
        if (tag == 8) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &guid_)));
          set_has_guid();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(16)) goto parse_version;
        break;
      }

      // required int32 version = 2;
      case 2: {
        if (tag == 16) {
         parse_version:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &version_)));
          set_has_version();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectAtEnd()) goto success;
        break;
      }

      default: {
      handle_unusual:
        if (tag == 0 ||
            ::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          goto success;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, mutable_unknown_fields()));
        break;
      }
    }
  }
success:
  // @@protoc_insertion_point(parse_success:ProtoGateClient.Login)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:ProtoGateClient.Login)
  return false;
#undef DO_
}

void Login::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:ProtoGateClient.Login)
  // required uint32 guid = 1;
  if (has_guid()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(1, this->guid(), output);
  }

  // required int32 version = 2;
  if (has_version()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(2, this->version(), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:ProtoGateClient.Login)
}

::google::protobuf::uint8* Login::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:ProtoGateClient.Login)
  // required uint32 guid = 1;
  if (has_guid()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(1, this->guid(), target);
  }

  // required int32 version = 2;
  if (has_version()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(2, this->version(), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:ProtoGateClient.Login)
  return target;
}

int Login::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // required uint32 guid = 1;
    if (has_guid()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->guid());
    }

    // required int32 version = 2;
    if (has_version()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->version());
    }

  }
  if (!unknown_fields().empty()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        unknown_fields());
  }
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void Login::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const Login* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const Login*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void Login::MergeFrom(const Login& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_guid()) {
      set_guid(from.guid());
    }
    if (from.has_version()) {
      set_version(from.version());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void Login::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void Login::CopyFrom(const Login& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Login::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000003) != 0x00000003) return false;

  return true;
}

void Login::Swap(Login* other) {
  if (other != this) {
    std::swap(guid_, other->guid_);
    std::swap(version_, other->version_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata Login::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = Login_descriptor_;
  metadata.reflection = Login_reflection_;
  return metadata;
}


// ===================================================================

#ifndef _MSC_VER
#endif  // !_MSC_VER

ListGameServer::ListGameServer()
  : ::google::protobuf::Message() {
  SharedCtor();
  // @@protoc_insertion_point(constructor:ProtoGateClient.ListGameServer)
}

void ListGameServer::InitAsDefaultInstance() {
}

ListGameServer::ListGameServer(const ListGameServer& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:ProtoGateClient.ListGameServer)
}

void ListGameServer::SharedCtor() {
  _cached_size_ = 0;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

ListGameServer::~ListGameServer() {
  // @@protoc_insertion_point(destructor:ProtoGateClient.ListGameServer)
  SharedDtor();
}

void ListGameServer::SharedDtor() {
  if (this != default_instance_) {
  }
}

void ListGameServer::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* ListGameServer::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return ListGameServer_descriptor_;
}

const ListGameServer& ListGameServer::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_ProtoGateClient_2eproto();
  return *default_instance_;
}

ListGameServer* ListGameServer::default_instance_ = NULL;

ListGameServer* ListGameServer::New() const {
  return new ListGameServer;
}

void ListGameServer::Clear() {
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool ListGameServer::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:ProtoGateClient.ListGameServer)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
  handle_unusual:
    if (tag == 0 ||
        ::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
        ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
      goto success;
    }
    DO_(::google::protobuf::internal::WireFormat::SkipField(
          input, tag, mutable_unknown_fields()));
  }
success:
  // @@protoc_insertion_point(parse_success:ProtoGateClient.ListGameServer)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:ProtoGateClient.ListGameServer)
  return false;
#undef DO_
}

void ListGameServer::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:ProtoGateClient.ListGameServer)
  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:ProtoGateClient.ListGameServer)
}

::google::protobuf::uint8* ListGameServer::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:ProtoGateClient.ListGameServer)
  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:ProtoGateClient.ListGameServer)
  return target;
}

int ListGameServer::ByteSize() const {
  int total_size = 0;

  if (!unknown_fields().empty()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        unknown_fields());
  }
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void ListGameServer::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const ListGameServer* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const ListGameServer*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void ListGameServer::MergeFrom(const ListGameServer& from) {
  GOOGLE_CHECK_NE(&from, this);
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void ListGameServer::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void ListGameServer::CopyFrom(const ListGameServer& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool ListGameServer::IsInitialized() const {

  return true;
}

void ListGameServer::Swap(ListGameServer* other) {
  if (other != this) {
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata ListGameServer::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = ListGameServer_descriptor_;
  metadata.reflection = ListGameServer_reflection_;
  return metadata;
}


// ===================================================================

#ifndef _MSC_VER
const int SendToPlayer::kGuidFieldNumber;
const int SendToPlayer::kSizeFieldNumber;
const int SendToPlayer::kDataFieldNumber;
const int SendToPlayer::kPlayersFieldNumber;
#endif  // !_MSC_VER

SendToPlayer::SendToPlayer()
  : ::google::protobuf::Message() {
  SharedCtor();
  // @@protoc_insertion_point(constructor:ProtoGateClient.SendToPlayer)
}

void SendToPlayer::InitAsDefaultInstance() {
}

SendToPlayer::SendToPlayer(const SendToPlayer& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:ProtoGateClient.SendToPlayer)
}

void SendToPlayer::SharedCtor() {
  ::google::protobuf::internal::GetEmptyString();
  _cached_size_ = 0;
  guid_ = 0u;
  size_ = 0;
  data_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

SendToPlayer::~SendToPlayer() {
  // @@protoc_insertion_point(destructor:ProtoGateClient.SendToPlayer)
  SharedDtor();
}

void SendToPlayer::SharedDtor() {
  if (data_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete data_;
  }
  if (this != default_instance_) {
  }
}

void SendToPlayer::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* SendToPlayer::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return SendToPlayer_descriptor_;
}

const SendToPlayer& SendToPlayer::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_ProtoGateClient_2eproto();
  return *default_instance_;
}

SendToPlayer* SendToPlayer::default_instance_ = NULL;

SendToPlayer* SendToPlayer::New() const {
  return new SendToPlayer;
}

void SendToPlayer::Clear() {
#define OFFSET_OF_FIELD_(f) (reinterpret_cast<char*>(      \
  &reinterpret_cast<SendToPlayer*>(16)->f) - \
   reinterpret_cast<char*>(16))

#define ZR_(first, last) do {                              \
    size_t f = OFFSET_OF_FIELD_(first);                    \
    size_t n = OFFSET_OF_FIELD_(last) - f + sizeof(last);  \
    ::memset(&first, 0, n);                                \
  } while (0)

  if (_has_bits_[0 / 32] & 7) {
    ZR_(guid_, size_);
    if (has_data()) {
      if (data_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
        data_->clear();
      }
    }
  }

#undef OFFSET_OF_FIELD_
#undef ZR_

  players_.Clear();
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool SendToPlayer::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:ProtoGateClient.SendToPlayer)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required uint32 guid = 1;
      case 1: {
        if (tag == 8) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &guid_)));
          set_has_guid();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(16)) goto parse_size;
        break;
      }

      // required int32 size = 2;
      case 2: {
        if (tag == 16) {
         parse_size:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &size_)));
          set_has_size();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(26)) goto parse_data;
        break;
      }

      // required bytes data = 3;
      case 3: {
        if (tag == 26) {
         parse_data:
          DO_(::google::protobuf::internal::WireFormatLite::ReadBytes(
                input, this->mutable_data()));
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(32)) goto parse_players;
        break;
      }

      // repeated int32 players = 4;
      case 4: {
        if (tag == 32) {
         parse_players:
          DO_((::google::protobuf::internal::WireFormatLite::ReadRepeatedPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 1, 32, input, this->mutable_players())));
        } else if (tag == 34) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPackedPrimitiveNoInline<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, this->mutable_players())));
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(32)) goto parse_players;
        if (input->ExpectAtEnd()) goto success;
        break;
      }

      default: {
      handle_unusual:
        if (tag == 0 ||
            ::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          goto success;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, mutable_unknown_fields()));
        break;
      }
    }
  }
success:
  // @@protoc_insertion_point(parse_success:ProtoGateClient.SendToPlayer)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:ProtoGateClient.SendToPlayer)
  return false;
#undef DO_
}

void SendToPlayer::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:ProtoGateClient.SendToPlayer)
  // required uint32 guid = 1;
  if (has_guid()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(1, this->guid(), output);
  }

  // required int32 size = 2;
  if (has_size()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(2, this->size(), output);
  }

  // required bytes data = 3;
  if (has_data()) {
    ::google::protobuf::internal::WireFormatLite::WriteBytesMaybeAliased(
      3, this->data(), output);
  }

  // repeated int32 players = 4;
  for (int i = 0; i < this->players_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(
      4, this->players(i), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:ProtoGateClient.SendToPlayer)
}

::google::protobuf::uint8* SendToPlayer::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:ProtoGateClient.SendToPlayer)
  // required uint32 guid = 1;
  if (has_guid()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(1, this->guid(), target);
  }

  // required int32 size = 2;
  if (has_size()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(2, this->size(), target);
  }

  // required bytes data = 3;
  if (has_data()) {
    target =
      ::google::protobuf::internal::WireFormatLite::WriteBytesToArray(
        3, this->data(), target);
  }

  // repeated int32 players = 4;
  for (int i = 0; i < this->players_size(); i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteInt32ToArray(4, this->players(i), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:ProtoGateClient.SendToPlayer)
  return target;
}

int SendToPlayer::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // required uint32 guid = 1;
    if (has_guid()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->guid());
    }

    // required int32 size = 2;
    if (has_size()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->size());
    }

    // required bytes data = 3;
    if (has_data()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::BytesSize(
          this->data());
    }

  }
  // repeated int32 players = 4;
  {
    int data_size = 0;
    for (int i = 0; i < this->players_size(); i++) {
      data_size += ::google::protobuf::internal::WireFormatLite::
        Int32Size(this->players(i));
    }
    total_size += 1 * this->players_size() + data_size;
  }

  if (!unknown_fields().empty()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        unknown_fields());
  }
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void SendToPlayer::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const SendToPlayer* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const SendToPlayer*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void SendToPlayer::MergeFrom(const SendToPlayer& from) {
  GOOGLE_CHECK_NE(&from, this);
  players_.MergeFrom(from.players_);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_guid()) {
      set_guid(from.guid());
    }
    if (from.has_size()) {
      set_size(from.size());
    }
    if (from.has_data()) {
      set_data(from.data());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void SendToPlayer::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void SendToPlayer::CopyFrom(const SendToPlayer& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool SendToPlayer::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000007) != 0x00000007) return false;

  return true;
}

void SendToPlayer::Swap(SendToPlayer* other) {
  if (other != this) {
    std::swap(guid_, other->guid_);
    std::swap(size_, other->size_);
    std::swap(data_, other->data_);
    players_.Swap(&other->players_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata SendToPlayer::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = SendToPlayer_descriptor_;
  metadata.reflection = SendToPlayer_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace ProtoGateClient

// @@protoc_insertion_point(global_scope)
