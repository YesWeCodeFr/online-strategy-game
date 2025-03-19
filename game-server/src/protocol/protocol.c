#include "protocol.h"
#include "generated/message_types.pb-c.h"
#include "generated/message_envelope.pb-c.h"
#include "generated/messages.pb-c.h"
#include <stdlib.h>
#include <string.h>

// Fonction pour encoder un message
uint8_t* encode_message(int request_id, int message_type, void* payload, size_t payload_size, size_t* output_size) {
    // Créer l'enveloppe
    Gameprotocol__MessageEnvelope envelope = GAMEPROTOCOL__MESSAGE_ENVELOPE__INIT;
    
    envelope.requestid = request_id;
    envelope.type = message_type;
    envelope.payload.data = payload;
    envelope.payload.len = payload_size;
    
    // Calculer la taille nécessaire
    *output_size = gameprotocol__message_envelope__get_packed_size(&envelope);
    
    // Allouer la mémoire pour le message encodé
    uint8_t* buffer = malloc(*output_size);
    if (!buffer) {
        return NULL;
    }
    
    // Encoder le message
    gameprotocol__message_envelope__pack(&envelope, buffer);
    
    return buffer;
}

// Fonction pour décoder un message
message_data_t* decode_message(const uint8_t* buffer, size_t buffer_size) {
    // Décoder l'enveloppe
    Gameprotocol__MessageEnvelope* envelope = 
        gameprotocol__message_envelope__unpack(NULL, buffer_size, buffer);
    
    if (!envelope) {
        return NULL;
    }
    
    // Allouer la structure de retour
    message_data_t* result = malloc(sizeof(message_data_t));
    if (!result) {
        gameprotocol__message_envelope__free_unpacked(envelope, NULL);
        return NULL;
    }
    
    // Remplir les informations de base
    result->request_id = envelope->requestid;
    result->type = envelope->type;
    result->payload = NULL;
    result->payload_size = 0;
    
    // Stocker le payload pour un traitement ultérieur
    if (envelope->payload.len > 0) {
        result->payload = malloc(envelope->payload.len);
        if (result->payload) {
            memcpy(result->payload, envelope->payload.data, envelope->payload.len);
            result->payload_size = envelope->payload.len;
        }
    }
    
    // Libérer l'enveloppe
    gameprotocol__message_envelope__free_unpacked(envelope, NULL);
    
    return result;
}

// Fonction pour libérer un message décodé
void free_message_data(message_data_t* message) {
    if (message) {
        if (message->payload) {
            free(message->payload);
        }
        free(message);
    }
} 