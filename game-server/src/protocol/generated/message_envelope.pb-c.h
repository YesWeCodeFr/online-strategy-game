/* Generated by the protocol buffer compiler.  DO NOT EDIT! */
/* Generated from: message_envelope.proto */

#ifndef PROTOBUF_C_message_5fenvelope_2eproto__INCLUDED
#define PROTOBUF_C_message_5fenvelope_2eproto__INCLUDED

#include <protobuf-c/protobuf-c.h>

PROTOBUF_C__BEGIN_DECLS

#if PROTOBUF_C_VERSION_NUMBER < 1003000
# error This file was generated by a newer version of protoc-c which is incompatible with your libprotobuf-c headers. Please update your headers.
#elif 1004001 < PROTOBUF_C_MIN_COMPILER_VERSION
# error This file was generated by an older version of protoc-c which is incompatible with your libprotobuf-c headers. Please regenerate this file with a newer version of protoc-c.
#endif

#include "message_types.pb-c.h"

typedef struct Gameprotocol__MessageEnvelope Gameprotocol__MessageEnvelope;


/* --- enums --- */


/* --- messages --- */

/*
 * Enveloppe ultra-compacte pour tous les messages
 */
struct  Gameprotocol__MessageEnvelope
{
  ProtobufCMessage base;
  Gameprotocol__MessageType type;
  ProtobufCBinaryData payload;
};
#define GAMEPROTOCOL__MESSAGE_ENVELOPE__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&gameprotocol__message_envelope__descriptor) \
    , GAMEPROTOCOL__MESSAGE_TYPE__MESSAGE_TYPE_UNKNOWN, {0,NULL} }


/* Gameprotocol__MessageEnvelope methods */
void   gameprotocol__message_envelope__init
                     (Gameprotocol__MessageEnvelope         *message);
size_t gameprotocol__message_envelope__get_packed_size
                     (const Gameprotocol__MessageEnvelope   *message);
size_t gameprotocol__message_envelope__pack
                     (const Gameprotocol__MessageEnvelope   *message,
                      uint8_t             *out);
size_t gameprotocol__message_envelope__pack_to_buffer
                     (const Gameprotocol__MessageEnvelope   *message,
                      ProtobufCBuffer     *buffer);
Gameprotocol__MessageEnvelope *
       gameprotocol__message_envelope__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   gameprotocol__message_envelope__free_unpacked
                     (Gameprotocol__MessageEnvelope *message,
                      ProtobufCAllocator *allocator);
/* --- per-message closures --- */

typedef void (*Gameprotocol__MessageEnvelope_Closure)
                 (const Gameprotocol__MessageEnvelope *message,
                  void *closure_data);

/* --- services --- */


/* --- descriptors --- */

extern const ProtobufCMessageDescriptor gameprotocol__message_envelope__descriptor;

PROTOBUF_C__END_DECLS


#endif  /* PROTOBUF_C_message_5fenvelope_2eproto__INCLUDED */
