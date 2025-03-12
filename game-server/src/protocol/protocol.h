#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <stdint.h>
#include <stddef.h>

// Types de messages
enum MessageType {
  MESSAGE_TYPE_UNKNOWN = 0,
  MESSAGE_TYPE_HELLO = 1,
  MESSAGE_TYPE_ADD_PLAYER = 2,
  MESSAGE_TYPE_GET_PLAYER_LIST = 3,
  MESSAGE_TYPE_PLAYER_LIST = 4
};

// Structure pour stocker les données d'un message décodé
typedef struct {
  int type;
  void* payload;
  size_t payload_size;
} message_data_t;

// Fonction pour encoder un message
uint8_t* encode_message(int message_type, void* payload, size_t payload_size, size_t* output_size);

// Fonction pour décoder un message
message_data_t* decode_message(const uint8_t* buffer, size_t buffer_size);

// Fonction pour libérer un message décodé
void free_message_data(message_data_t* message);

#endif // PROTOCOL_H 