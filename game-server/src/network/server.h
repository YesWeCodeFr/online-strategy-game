#ifndef SERVER_H
#define SERVER_H

#include "../game_server.h"
#include "../protocol/protocol.h"
#include <stdint.h>
#include <stddef.h>

// Initialiser le serveur sur un port spécifique
int init_server(int port);

// Démarrer la boucle d'écoute du serveur
void start_server_loop(GameServer* gameServer);

// Arrêter le serveur
void stop_server(int server_socket);

// Fonctions de gestion des messages
void handle_message(int client_socket, message_data_t* message, GameServer* gameServer);
void handle_hello(int client_socket, int request_id, const void* payload, size_t payload_size);
void handle_add_player(int client_socket, int request_id, const void* payload, size_t payload_size, GameServer* gameServer);
void handle_get_player_list(int client_socket, int request_id, const void* payload, size_t payload_size, GameServer* gameServer);

#endif // SERVER_H 