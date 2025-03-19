/* Generated by the protocol buffer compiler.  DO NOT EDIT! */
/* Generated from: message_envelope.proto */

/* Do not generate deprecated warnings for self */
#ifndef PROTOBUF_C__NO_DEPRECATED
#define PROTOBUF_C__NO_DEPRECATED
#endif

#include "message_envelope.pb-c.h"
void   gameprotocol__message_envelope__init
                     (Gameprotocol__MessageEnvelope         *message)
{
  static const Gameprotocol__MessageEnvelope init_value = GAMEPROTOCOL__MESSAGE_ENVELOPE__INIT;
  *message = init_value;
}
size_t gameprotocol__message_envelope__get_packed_size
                     (const Gameprotocol__MessageEnvelope *message)
{
  assert(message->base.descriptor == &gameprotocol__message_envelope__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t gameprotocol__message_envelope__pack
                     (const Gameprotocol__MessageEnvelope *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &gameprotocol__message_envelope__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t gameprotocol__message_envelope__pack_to_buffer
                     (const Gameprotocol__MessageEnvelope *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &gameprotocol__message_envelope__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
Gameprotocol__MessageEnvelope *
       gameprotocol__message_envelope__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (Gameprotocol__MessageEnvelope *)
     protobuf_c_message_unpack (&gameprotocol__message_envelope__descriptor,
                                allocator, len, data);
}
void   gameprotocol__message_envelope__free_unpacked
                     (Gameprotocol__MessageEnvelope *message,
                      ProtobufCAllocator *allocator)
{
  if(!message)
    return;
  assert(message->base.descriptor == &gameprotocol__message_envelope__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
static const ProtobufCFieldDescriptor gameprotocol__message_envelope__field_descriptors[3] =
{
  {
    "requestId",
    1,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_UINT32,
    0,   /* quantifier_offset */
    offsetof(Gameprotocol__MessageEnvelope, requestid),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "type",
    2,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_ENUM,
    0,   /* quantifier_offset */
    offsetof(Gameprotocol__MessageEnvelope, type),
    &gameprotocol__message_type__descriptor,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "payload",
    3,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_BYTES,
    0,   /* quantifier_offset */
    offsetof(Gameprotocol__MessageEnvelope, payload),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned gameprotocol__message_envelope__field_indices_by_name[] = {
  2,   /* field[2] = payload */
  0,   /* field[0] = requestId */
  1,   /* field[1] = type */
};
static const ProtobufCIntRange gameprotocol__message_envelope__number_ranges[1 + 1] =
{
  { 1, 0 },
  { 0, 3 }
};
const ProtobufCMessageDescriptor gameprotocol__message_envelope__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "gameprotocol.MessageEnvelope",
  "MessageEnvelope",
  "Gameprotocol__MessageEnvelope",
  "gameprotocol",
  sizeof(Gameprotocol__MessageEnvelope),
  3,
  gameprotocol__message_envelope__field_descriptors,
  gameprotocol__message_envelope__field_indices_by_name,
  1,  gameprotocol__message_envelope__number_ranges,
  (ProtobufCMessageInit) gameprotocol__message_envelope__init,
  NULL,NULL,NULL    /* reserved[123] */
};
