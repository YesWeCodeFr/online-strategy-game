/* Generated by the protocol buffer compiler.  DO NOT EDIT! */
/* Generated from: messages.proto */

/* Do not generate deprecated warnings for self */
#ifndef PROTOBUF_C__NO_DEPRECATED
#define PROTOBUF_C__NO_DEPRECATED
#endif

#include "messages.pb-c.h"
void   gameprotocol__hello__init
                     (Gameprotocol__Hello         *message)
{
  static const Gameprotocol__Hello init_value = GAMEPROTOCOL__HELLO__INIT;
  *message = init_value;
}
size_t gameprotocol__hello__get_packed_size
                     (const Gameprotocol__Hello *message)
{
  assert(message->base.descriptor == &gameprotocol__hello__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t gameprotocol__hello__pack
                     (const Gameprotocol__Hello *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &gameprotocol__hello__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t gameprotocol__hello__pack_to_buffer
                     (const Gameprotocol__Hello *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &gameprotocol__hello__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
Gameprotocol__Hello *
       gameprotocol__hello__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (Gameprotocol__Hello *)
     protobuf_c_message_unpack (&gameprotocol__hello__descriptor,
                                allocator, len, data);
}
void   gameprotocol__hello__free_unpacked
                     (Gameprotocol__Hello *message,
                      ProtobufCAllocator *allocator)
{
  if(!message)
    return;
  assert(message->base.descriptor == &gameprotocol__hello__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
void   gameprotocol__add_player__init
                     (Gameprotocol__AddPlayer         *message)
{
  static const Gameprotocol__AddPlayer init_value = GAMEPROTOCOL__ADD_PLAYER__INIT;
  *message = init_value;
}
size_t gameprotocol__add_player__get_packed_size
                     (const Gameprotocol__AddPlayer *message)
{
  assert(message->base.descriptor == &gameprotocol__add_player__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t gameprotocol__add_player__pack
                     (const Gameprotocol__AddPlayer *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &gameprotocol__add_player__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t gameprotocol__add_player__pack_to_buffer
                     (const Gameprotocol__AddPlayer *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &gameprotocol__add_player__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
Gameprotocol__AddPlayer *
       gameprotocol__add_player__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (Gameprotocol__AddPlayer *)
     protobuf_c_message_unpack (&gameprotocol__add_player__descriptor,
                                allocator, len, data);
}
void   gameprotocol__add_player__free_unpacked
                     (Gameprotocol__AddPlayer *message,
                      ProtobufCAllocator *allocator)
{
  if(!message)
    return;
  assert(message->base.descriptor == &gameprotocol__add_player__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
void   gameprotocol__get_player_list__init
                     (Gameprotocol__GetPlayerList         *message)
{
  static const Gameprotocol__GetPlayerList init_value = GAMEPROTOCOL__GET_PLAYER_LIST__INIT;
  *message = init_value;
}
size_t gameprotocol__get_player_list__get_packed_size
                     (const Gameprotocol__GetPlayerList *message)
{
  assert(message->base.descriptor == &gameprotocol__get_player_list__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t gameprotocol__get_player_list__pack
                     (const Gameprotocol__GetPlayerList *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &gameprotocol__get_player_list__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t gameprotocol__get_player_list__pack_to_buffer
                     (const Gameprotocol__GetPlayerList *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &gameprotocol__get_player_list__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
Gameprotocol__GetPlayerList *
       gameprotocol__get_player_list__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (Gameprotocol__GetPlayerList *)
     protobuf_c_message_unpack (&gameprotocol__get_player_list__descriptor,
                                allocator, len, data);
}
void   gameprotocol__get_player_list__free_unpacked
                     (Gameprotocol__GetPlayerList *message,
                      ProtobufCAllocator *allocator)
{
  if(!message)
    return;
  assert(message->base.descriptor == &gameprotocol__get_player_list__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
void   gameprotocol__player_list__init
                     (Gameprotocol__PlayerList         *message)
{
  static const Gameprotocol__PlayerList init_value = GAMEPROTOCOL__PLAYER_LIST__INIT;
  *message = init_value;
}
size_t gameprotocol__player_list__get_packed_size
                     (const Gameprotocol__PlayerList *message)
{
  assert(message->base.descriptor == &gameprotocol__player_list__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t gameprotocol__player_list__pack
                     (const Gameprotocol__PlayerList *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &gameprotocol__player_list__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t gameprotocol__player_list__pack_to_buffer
                     (const Gameprotocol__PlayerList *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &gameprotocol__player_list__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
Gameprotocol__PlayerList *
       gameprotocol__player_list__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (Gameprotocol__PlayerList *)
     protobuf_c_message_unpack (&gameprotocol__player_list__descriptor,
                                allocator, len, data);
}
void   gameprotocol__player_list__free_unpacked
                     (Gameprotocol__PlayerList *message,
                      ProtobufCAllocator *allocator)
{
  if(!message)
    return;
  assert(message->base.descriptor == &gameprotocol__player_list__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
void   gameprotocol__player__init
                     (Gameprotocol__Player         *message)
{
  static const Gameprotocol__Player init_value = GAMEPROTOCOL__PLAYER__INIT;
  *message = init_value;
}
size_t gameprotocol__player__get_packed_size
                     (const Gameprotocol__Player *message)
{
  assert(message->base.descriptor == &gameprotocol__player__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t gameprotocol__player__pack
                     (const Gameprotocol__Player *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &gameprotocol__player__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t gameprotocol__player__pack_to_buffer
                     (const Gameprotocol__Player *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &gameprotocol__player__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
Gameprotocol__Player *
       gameprotocol__player__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (Gameprotocol__Player *)
     protobuf_c_message_unpack (&gameprotocol__player__descriptor,
                                allocator, len, data);
}
void   gameprotocol__player__free_unpacked
                     (Gameprotocol__Player *message,
                      ProtobufCAllocator *allocator)
{
  if(!message)
    return;
  assert(message->base.descriptor == &gameprotocol__player__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
static const ProtobufCFieldDescriptor gameprotocol__hello__field_descriptors[1] =
{
  {
    "version",
    1,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_UINT32,
    0,   /* quantifier_offset */
    offsetof(Gameprotocol__Hello, version),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned gameprotocol__hello__field_indices_by_name[] = {
  0,   /* field[0] = version */
};
static const ProtobufCIntRange gameprotocol__hello__number_ranges[1 + 1] =
{
  { 1, 0 },
  { 0, 1 }
};
const ProtobufCMessageDescriptor gameprotocol__hello__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "gameprotocol.Hello",
  "Hello",
  "Gameprotocol__Hello",
  "gameprotocol",
  sizeof(Gameprotocol__Hello),
  1,
  gameprotocol__hello__field_descriptors,
  gameprotocol__hello__field_indices_by_name,
  1,  gameprotocol__hello__number_ranges,
  (ProtobufCMessageInit) gameprotocol__hello__init,
  NULL,NULL,NULL    /* reserved[123] */
};
static const ProtobufCFieldDescriptor gameprotocol__add_player__field_descriptors[2] =
{
  {
    "player_id",
    1,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_UINT32,
    0,   /* quantifier_offset */
    offsetof(Gameprotocol__AddPlayer, player_id),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "username",
    2,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_STRING,
    0,   /* quantifier_offset */
    offsetof(Gameprotocol__AddPlayer, username),
    NULL,
    &protobuf_c_empty_string,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned gameprotocol__add_player__field_indices_by_name[] = {
  0,   /* field[0] = player_id */
  1,   /* field[1] = username */
};
static const ProtobufCIntRange gameprotocol__add_player__number_ranges[1 + 1] =
{
  { 1, 0 },
  { 0, 2 }
};
const ProtobufCMessageDescriptor gameprotocol__add_player__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "gameprotocol.AddPlayer",
  "AddPlayer",
  "Gameprotocol__AddPlayer",
  "gameprotocol",
  sizeof(Gameprotocol__AddPlayer),
  2,
  gameprotocol__add_player__field_descriptors,
  gameprotocol__add_player__field_indices_by_name,
  1,  gameprotocol__add_player__number_ranges,
  (ProtobufCMessageInit) gameprotocol__add_player__init,
  NULL,NULL,NULL    /* reserved[123] */
};
#define gameprotocol__get_player_list__field_descriptors NULL
#define gameprotocol__get_player_list__field_indices_by_name NULL
#define gameprotocol__get_player_list__number_ranges NULL
const ProtobufCMessageDescriptor gameprotocol__get_player_list__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "gameprotocol.GetPlayerList",
  "GetPlayerList",
  "Gameprotocol__GetPlayerList",
  "gameprotocol",
  sizeof(Gameprotocol__GetPlayerList),
  0,
  gameprotocol__get_player_list__field_descriptors,
  gameprotocol__get_player_list__field_indices_by_name,
  0,  gameprotocol__get_player_list__number_ranges,
  (ProtobufCMessageInit) gameprotocol__get_player_list__init,
  NULL,NULL,NULL    /* reserved[123] */
};
static const ProtobufCFieldDescriptor gameprotocol__player_list__field_descriptors[1] =
{
  {
    "players",
    1,
    PROTOBUF_C_LABEL_REPEATED,
    PROTOBUF_C_TYPE_MESSAGE,
    offsetof(Gameprotocol__PlayerList, n_players),
    offsetof(Gameprotocol__PlayerList, players),
    &gameprotocol__player__descriptor,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned gameprotocol__player_list__field_indices_by_name[] = {
  0,   /* field[0] = players */
};
static const ProtobufCIntRange gameprotocol__player_list__number_ranges[1 + 1] =
{
  { 1, 0 },
  { 0, 1 }
};
const ProtobufCMessageDescriptor gameprotocol__player_list__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "gameprotocol.PlayerList",
  "PlayerList",
  "Gameprotocol__PlayerList",
  "gameprotocol",
  sizeof(Gameprotocol__PlayerList),
  1,
  gameprotocol__player_list__field_descriptors,
  gameprotocol__player_list__field_indices_by_name,
  1,  gameprotocol__player_list__number_ranges,
  (ProtobufCMessageInit) gameprotocol__player_list__init,
  NULL,NULL,NULL    /* reserved[123] */
};
static const ProtobufCFieldDescriptor gameprotocol__player__field_descriptors[2] =
{
  {
    "player_id",
    1,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_UINT32,
    0,   /* quantifier_offset */
    offsetof(Gameprotocol__Player, player_id),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "username",
    2,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_STRING,
    0,   /* quantifier_offset */
    offsetof(Gameprotocol__Player, username),
    NULL,
    &protobuf_c_empty_string,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned gameprotocol__player__field_indices_by_name[] = {
  0,   /* field[0] = player_id */
  1,   /* field[1] = username */
};
static const ProtobufCIntRange gameprotocol__player__number_ranges[1 + 1] =
{
  { 1, 0 },
  { 0, 2 }
};
const ProtobufCMessageDescriptor gameprotocol__player__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "gameprotocol.Player",
  "Player",
  "Gameprotocol__Player",
  "gameprotocol",
  sizeof(Gameprotocol__Player),
  2,
  gameprotocol__player__field_descriptors,
  gameprotocol__player__field_indices_by_name,
  1,  gameprotocol__player__number_ranges,
  (ProtobufCMessageInit) gameprotocol__player__init,
  NULL,NULL,NULL    /* reserved[123] */
};
