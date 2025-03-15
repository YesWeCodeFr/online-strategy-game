#include "server.h"
#include "../protocol/protocol.h"
#include "../protocol/generated/messages.pb-c.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

// Fonction pour gérer un message HELLO
void handle_hello(int client_socket, const void* payload, size_t payload_size) {
    // Décoder le message Hello
    Gameprotocol__Hello* hello = gameprotocol__hello__unpack(NULL, payload_size, payload);
    if (!hello) {
        printf("Erreur de décodage du message Hello\n");
        return;
    }
    
    printf("Message HELLO reçu, version: %u\n", hello->version);
    
    // Répondre avec un HELLO
    Gameprotocol__Hello response = GAMEPROTOCOL__HELLO__INIT;
    response.version = 1; // Notre version
    
    // Encoder le message
    size_t response_size = gameprotocol__hello__get_packed_size(&response);
    uint8_t* response_buffer = malloc(response_size);
    gameprotocol__hello__pack(&response, response_buffer);
    
    // Envoyer la réponse
    size_t envelope_size;
    uint8_t* envelope_buffer = encode_message(MESSAGE_TYPE_HELLO, response_buffer, response_size, &envelope_size);
    
    if (envelope_buffer) {
        send(client_socket, envelope_buffer, envelope_size, 0);
        free(envelope_buffer);
    }
    
    free(response_buffer);
    gameprotocol__hello__free_unpacked(hello, NULL);
}

// Fonction pour gérer un message ADD_PLAYER
void handle_add_player(int client_socket, const void* payload, size_t payload_size) {
    // Décoder le message AddPlayer
    Gameprotocol__AddPlayer* add_player = gameprotocol__add_player__unpack(NULL, payload_size, payload);
    if (!add_player) {
        printf("Erreur de décodage du message AddPlayer\n");
        return;
    }
    
    printf("Message ADD_PLAYER reçu, id: %u, nom: %s\n", add_player->player_id, add_player->username);
    
    // Ajouter le joueur à la liste (code non inclus)
    // ...
    
    gameprotocol__add_player__free_unpacked(add_player, NULL);
}

// Fonction pour gérer un message GET_PLAYER_LIST
void handle_get_player_list(int client_socket, const void* payload, size_t payload_size) {
    printf("Message GET_PLAYER_LIST reçu\n");
    
    // Créer une liste de joueurs (exemple)
    Gameprotocol__Player players[2];
    Gameprotocol__Player player1 = GAMEPROTOCOL__PLAYER__INIT;
    Gameprotocol__Player player2 = GAMEPROTOCOL__PLAYER__INIT;
    
    player1.player_id = 1;
    player1.username = "Joueur1";    
    
    player2.player_id = 2;
    player2.username = "Joueur2";    
    
    players[0] = player1;
    players[1] = player2;
    
    // Créer le message PlayerList
    Gameprotocol__PlayerList player_list = GAMEPROTOCOL__PLAYER_LIST__INIT;
    player_list.n_players = 2;
    player_list.players = players;
    
    // Encoder le message
    size_t response_size = gameprotocol__player_list__get_packed_size(&player_list);
    uint8_t* response_buffer = malloc(response_size);
    gameprotocol__player_list__pack(&player_list, response_buffer);
    
    // Envoyer la réponse
    size_t envelope_size;
    uint8_t* envelope_buffer = encode_message(MESSAGE_TYPE_PLAYER_LIST, response_buffer, response_size, &envelope_size);
    
    if (envelope_buffer) {
        send(client_socket, envelope_buffer, envelope_size, 0);
        free(envelope_buffer);
    }
    
    free(response_buffer);
}

// Fonction pour traiter un message reçu
void handle_message(int client_socket, message_data_t* message) {
    printf("Message reçu\n");
    switch (message->type) {
        case MESSAGE_TYPE_HELLO:
            handle_hello(client_socket, message->payload, message->payload_size);
            break;
        case MESSAGE_TYPE_ADD_PLAYER:
            handle_add_player(client_socket, message->payload, message->payload_size);
            break;
        case MESSAGE_TYPE_GET_PLAYER_LIST:
            handle_get_player_list(client_socket, message->payload, message->payload_size);
            break;
        default:
            printf("Type de message inconnu: %d\n", message->type);
    }
}

// Initialiser le serveur sur un port spécifique
int init_server(int port) {
    int server_socket;
    struct sockaddr_in server_addr;
    
    // Créer le socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) {
        perror("Erreur lors de la création du socket");
        return -1;
    }
    
    // Configurer l'adresse du serveur
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port);
    
    // Lier le socket à l'adresse
    if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Erreur lors du bind");
        close(server_socket);
        return -1;
    }
    
    // Mettre le socket en mode écoute
    if (listen(server_socket, 5) < 0) {
        perror("Erreur lors de l'écoute");
        close(server_socket);
        return -1;
    }
    
    printf("Serveur démarré sur le port %d\n", port);
    
    return server_socket;
}

// Démarrer la boucle d'écoute du serveur
void start_server_loop(int server_socket) {
    int client_socket;
    struct sockaddr_in client_addr;
    socklen_t client_len = sizeof(client_addr);
    uint8_t buffer[4096];
    ssize_t bytes_read;
    
    printf("En attente de connexions...\n");
    
    while (1) {
        // Accepter une nouvelle connexion
        client_socket = accept(server_socket, (struct sockaddr*)&client_addr, &client_len);
        if (client_socket < 0) {
            perror("Erreur lors de l'acceptation de la connexion");
            continue;
        }
        
        printf("Nouvelle connexion acceptée\n");
        
        // Boucle de lecture des messages
        while ((bytes_read = recv(client_socket, buffer, sizeof(buffer), 0)) > 0) {
            // Décoder le message
            message_data_t* message = decode_message(buffer, bytes_read);
            if (message) {
                // Traiter le message
                handle_message(client_socket, message);
                free_message_data(message);
            } else {
                printf("Erreur lors de la décodage du message\n");
            }
        }
        
        // Fermer la connexion client
        close(client_socket);
        printf("Connexion fermée\n");
    }
}

// Arrêter le serveur
void stop_server(int server_socket) {
    if (server_socket >= 0) {
        close(server_socket);
        printf("Serveur arrêté\n");
    }
} 