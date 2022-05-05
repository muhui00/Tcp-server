// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: person.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_person_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_person_2eproto

#include <limits>
#include <string>

#include <google/protobuf/port_def.inc>
#if PROTOBUF_VERSION < 3008000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers. Please update
#error your headers.
#endif
#if 3008000 < PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers. Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/port_undef.inc>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/inlined_string_field.h>
#include <google/protobuf/metadata.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/generated_enum_reflection.h>
#include <google/protobuf/unknown_field_set.h>
#include "info.pb.h"
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_person_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_person_2eproto {
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTableField entries[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::AuxillaryParseTableField aux[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTable schema[1]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::FieldMetadata field_metadata[];
  static const ::PROTOBUF_NAMESPACE_ID::internal::SerializationTable serialization_table[];
  static const ::PROTOBUF_NAMESPACE_ID::uint32 offsets[];
};
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_person_2eproto;
namespace a {
class Person;
class PersonDefaultTypeInternal;
extern PersonDefaultTypeInternal _Person_default_instance_;
}  // namespace a
PROTOBUF_NAMESPACE_OPEN
template<> ::a::Person* Arena::CreateMaybeMessage<::a::Person>(Arena*);
PROTOBUF_NAMESPACE_CLOSE
namespace a {

enum Color : int {
  Red = 0,
  Green = 6,
  Blue = 9,
  Color_INT_MIN_SENTINEL_DO_NOT_USE_ = std::numeric_limits<::PROTOBUF_NAMESPACE_ID::int32>::min(),
  Color_INT_MAX_SENTINEL_DO_NOT_USE_ = std::numeric_limits<::PROTOBUF_NAMESPACE_ID::int32>::max()
};
bool Color_IsValid(int value);
constexpr Color Color_MIN = Red;
constexpr Color Color_MAX = Blue;
constexpr int Color_ARRAYSIZE = Color_MAX + 1;

const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor* Color_descriptor();
template<typename T>
inline const std::string& Color_Name(T enum_t_value) {
  static_assert(::std::is_same<T, Color>::value ||
    ::std::is_integral<T>::value,
    "Incorrect type passed to function Color_Name.");
  return ::PROTOBUF_NAMESPACE_ID::internal::NameOfEnum(
    Color_descriptor(), enum_t_value);
}
inline bool Color_Parse(
    const std::string& name, Color* value) {
  return ::PROTOBUF_NAMESPACE_ID::internal::ParseNamedEnum<Color>(
    Color_descriptor(), name, value);
}
// ===================================================================

class Person :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:a.Person) */ {
 public:
  Person();
  virtual ~Person();

  Person(const Person& from);
  Person(Person&& from) noexcept
    : Person() {
    *this = ::std::move(from);
  }

  inline Person& operator=(const Person& from) {
    CopyFrom(from);
    return *this;
  }
  inline Person& operator=(Person&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return GetMetadataStatic().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return GetMetadataStatic().reflection;
  }
  static const Person& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const Person* internal_default_instance() {
    return reinterpret_cast<const Person*>(
               &_Person_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  void Swap(Person* other);
  friend void swap(Person& a, Person& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline Person* New() const final {
    return CreateMaybeMessage<Person>(nullptr);
  }

  Person* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<Person>(arena);
  }
  void CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void CopyFrom(const Person& from);
  void MergeFrom(const Person& from);
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  #if GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  #else
  bool MergePartialFromCodedStream(
      ::PROTOBUF_NAMESPACE_ID::io::CodedInputStream* input) final;
  #endif  // GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
  void SerializeWithCachedSizes(
      ::PROTOBUF_NAMESPACE_ID::io::CodedOutputStream* output) const final;
  ::PROTOBUF_NAMESPACE_ID::uint8* InternalSerializeWithCachedSizesToArray(
      ::PROTOBUF_NAMESPACE_ID::uint8* target) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  inline void SharedCtor();
  inline void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(Person* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "a.Person";
  }
  private:
  inline ::PROTOBUF_NAMESPACE_ID::Arena* GetArenaNoVirtual() const {
    return nullptr;
  }
  inline void* MaybeArenaPtr() const {
    return nullptr;
  }
  public:

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;
  private:
  static ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadataStatic() {
    ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&::descriptor_table_person_2eproto);
    return ::descriptor_table_person_2eproto.file_level_metadata[kIndexInFileMessages];
  }

  public:

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // repeated bytes name = 2;
  int name_size() const;
  void clear_name();
  static const int kNameFieldNumber = 2;
  const std::string& name(int index) const;
  std::string* mutable_name(int index);
  void set_name(int index, const std::string& value);
  void set_name(int index, std::string&& value);
  void set_name(int index, const char* value);
  void set_name(int index, const void* value, size_t size);
  std::string* add_name();
  void add_name(const std::string& value);
  void add_name(std::string&& value);
  void add_name(const char* value);
  void add_name(const void* value, size_t size);
  const ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField<std::string>& name() const;
  ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField<std::string>* mutable_name();

  // string sex = 3;
  void clear_sex();
  static const int kSexFieldNumber = 3;
  const std::string& sex() const;
  void set_sex(const std::string& value);
  void set_sex(std::string&& value);
  void set_sex(const char* value);
  void set_sex(const char* value, size_t size);
  std::string* mutable_sex();
  std::string* release_sex();
  void set_allocated_sex(std::string* sex);

  // .b.Person info = 6;
  bool has_info() const;
  void clear_info();
  static const int kInfoFieldNumber = 6;
  const ::b::Person& info() const;
  ::b::Person* release_info();
  ::b::Person* mutable_info();
  void set_allocated_info(::b::Person* info);

  // int32 id = 1;
  void clear_id();
  static const int kIdFieldNumber = 1;
  ::PROTOBUF_NAMESPACE_ID::int32 id() const;
  void set_id(::PROTOBUF_NAMESPACE_ID::int32 value);

  // int32 age = 4;
  void clear_age();
  static const int kAgeFieldNumber = 4;
  ::PROTOBUF_NAMESPACE_ID::int32 age() const;
  void set_age(::PROTOBUF_NAMESPACE_ID::int32 value);

  // .a.Color color = 5;
  void clear_color();
  static const int kColorFieldNumber = 5;
  ::a::Color color() const;
  void set_color(::a::Color value);

  // @@protoc_insertion_point(class_scope:a.Person)
 private:
  class HasBitSetters;

  ::PROTOBUF_NAMESPACE_ID::internal::InternalMetadataWithArena _internal_metadata_;
  ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField<std::string> name_;
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr sex_;
  ::b::Person* info_;
  ::PROTOBUF_NAMESPACE_ID::int32 id_;
  ::PROTOBUF_NAMESPACE_ID::int32 age_;
  int color_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_person_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// Person

// int32 id = 1;
inline void Person::clear_id() {
  id_ = 0;
}
inline ::PROTOBUF_NAMESPACE_ID::int32 Person::id() const {
  // @@protoc_insertion_point(field_get:a.Person.id)
  return id_;
}
inline void Person::set_id(::PROTOBUF_NAMESPACE_ID::int32 value) {
  
  id_ = value;
  // @@protoc_insertion_point(field_set:a.Person.id)
}

// repeated bytes name = 2;
inline int Person::name_size() const {
  return name_.size();
}
inline void Person::clear_name() {
  name_.Clear();
}
inline const std::string& Person::name(int index) const {
  // @@protoc_insertion_point(field_get:a.Person.name)
  return name_.Get(index);
}
inline std::string* Person::mutable_name(int index) {
  // @@protoc_insertion_point(field_mutable:a.Person.name)
  return name_.Mutable(index);
}
inline void Person::set_name(int index, const std::string& value) {
  // @@protoc_insertion_point(field_set:a.Person.name)
  name_.Mutable(index)->assign(value);
}
inline void Person::set_name(int index, std::string&& value) {
  // @@protoc_insertion_point(field_set:a.Person.name)
  name_.Mutable(index)->assign(std::move(value));
}
inline void Person::set_name(int index, const char* value) {
  GOOGLE_DCHECK(value != nullptr);
  name_.Mutable(index)->assign(value);
  // @@protoc_insertion_point(field_set_char:a.Person.name)
}
inline void Person::set_name(int index, const void* value, size_t size) {
  name_.Mutable(index)->assign(
    reinterpret_cast<const char*>(value), size);
  // @@protoc_insertion_point(field_set_pointer:a.Person.name)
}
inline std::string* Person::add_name() {
  // @@protoc_insertion_point(field_add_mutable:a.Person.name)
  return name_.Add();
}
inline void Person::add_name(const std::string& value) {
  name_.Add()->assign(value);
  // @@protoc_insertion_point(field_add:a.Person.name)
}
inline void Person::add_name(std::string&& value) {
  name_.Add(std::move(value));
  // @@protoc_insertion_point(field_add:a.Person.name)
}
inline void Person::add_name(const char* value) {
  GOOGLE_DCHECK(value != nullptr);
  name_.Add()->assign(value);
  // @@protoc_insertion_point(field_add_char:a.Person.name)
}
inline void Person::add_name(const void* value, size_t size) {
  name_.Add()->assign(reinterpret_cast<const char*>(value), size);
  // @@protoc_insertion_point(field_add_pointer:a.Person.name)
}
inline const ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField<std::string>&
Person::name() const {
  // @@protoc_insertion_point(field_list:a.Person.name)
  return name_;
}
inline ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField<std::string>*
Person::mutable_name() {
  // @@protoc_insertion_point(field_mutable_list:a.Person.name)
  return &name_;
}

// string sex = 3;
inline void Person::clear_sex() {
  sex_.ClearToEmptyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline const std::string& Person::sex() const {
  // @@protoc_insertion_point(field_get:a.Person.sex)
  return sex_.GetNoArena();
}
inline void Person::set_sex(const std::string& value) {
  
  sex_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:a.Person.sex)
}
inline void Person::set_sex(std::string&& value) {
  
  sex_.SetNoArena(
    &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:a.Person.sex)
}
inline void Person::set_sex(const char* value) {
  GOOGLE_DCHECK(value != nullptr);
  
  sex_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:a.Person.sex)
}
inline void Person::set_sex(const char* value, size_t size) {
  
  sex_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:a.Person.sex)
}
inline std::string* Person::mutable_sex() {
  
  // @@protoc_insertion_point(field_mutable:a.Person.sex)
  return sex_.MutableNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline std::string* Person::release_sex() {
  // @@protoc_insertion_point(field_release:a.Person.sex)
  
  return sex_.ReleaseNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline void Person::set_allocated_sex(std::string* sex) {
  if (sex != nullptr) {
    
  } else {
    
  }
  sex_.SetAllocatedNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), sex);
  // @@protoc_insertion_point(field_set_allocated:a.Person.sex)
}

// int32 age = 4;
inline void Person::clear_age() {
  age_ = 0;
}
inline ::PROTOBUF_NAMESPACE_ID::int32 Person::age() const {
  // @@protoc_insertion_point(field_get:a.Person.age)
  return age_;
}
inline void Person::set_age(::PROTOBUF_NAMESPACE_ID::int32 value) {
  
  age_ = value;
  // @@protoc_insertion_point(field_set:a.Person.age)
}

// .a.Color color = 5;
inline void Person::clear_color() {
  color_ = 0;
}
inline ::a::Color Person::color() const {
  // @@protoc_insertion_point(field_get:a.Person.color)
  return static_cast< ::a::Color >(color_);
}
inline void Person::set_color(::a::Color value) {
  
  color_ = value;
  // @@protoc_insertion_point(field_set:a.Person.color)
}

// .b.Person info = 6;
inline bool Person::has_info() const {
  return this != internal_default_instance() && info_ != nullptr;
}
inline const ::b::Person& Person::info() const {
  const ::b::Person* p = info_;
  // @@protoc_insertion_point(field_get:a.Person.info)
  return p != nullptr ? *p : *reinterpret_cast<const ::b::Person*>(
      &::b::_Person_default_instance_);
}
inline ::b::Person* Person::release_info() {
  // @@protoc_insertion_point(field_release:a.Person.info)
  
  ::b::Person* temp = info_;
  info_ = nullptr;
  return temp;
}
inline ::b::Person* Person::mutable_info() {
  
  if (info_ == nullptr) {
    auto* p = CreateMaybeMessage<::b::Person>(GetArenaNoVirtual());
    info_ = p;
  }
  // @@protoc_insertion_point(field_mutable:a.Person.info)
  return info_;
}
inline void Person::set_allocated_info(::b::Person* info) {
  ::PROTOBUF_NAMESPACE_ID::Arena* message_arena = GetArenaNoVirtual();
  if (message_arena == nullptr) {
    delete reinterpret_cast< ::PROTOBUF_NAMESPACE_ID::MessageLite*>(info_);
  }
  if (info) {
    ::PROTOBUF_NAMESPACE_ID::Arena* submessage_arena = nullptr;
    if (message_arena != submessage_arena) {
      info = ::PROTOBUF_NAMESPACE_ID::internal::GetOwnedMessage(
          message_arena, info, submessage_arena);
    }
    
  } else {
    
  }
  info_ = info;
  // @@protoc_insertion_point(field_set_allocated:a.Person.info)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)

}  // namespace a

PROTOBUF_NAMESPACE_OPEN

template <> struct is_proto_enum< ::a::Color> : ::std::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::a::Color>() {
  return ::a::Color_descriptor();
}

PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_person_2eproto
