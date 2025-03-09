#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <signal.h>
#include "server.h"

// Variable globale pour accéder au serveur dans le gestionnaire de signal
static GameServer* globalServer = NULL;

// Gestionnaire de signal pour CTRL+C
static void handleSignal(int signal) {
    if (signal == SIGINT) {
        printf("\nFermeture du serveur...\n");
        if (globalServer) {
            cleanupServer(globalServer);
        }
        exit(0);
    }
}

void setupSignalHandler(GameServer* server) {
    globalServer = server;
    signal(SIGINT, handleSignal);
}

GameServer* createServer(void) {
    GameServer* server = malloc(sizeof(GameServer));
    server->players = createPlayerList(10);
    
    // Création du socket
    server->socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server->socket_fd < 0) {
        perror("Erreur lors de la création du socket");
        exit(1);
    }
    
    setupSignalHandler(server);
    
    return server;
}

void startServer(GameServer* server) {
    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
    
    if (bind(server->socket_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Erreur lors du bind");
        exit(1);
    }
    
    if (listen(server->socket_fd, 3) < 0) {
        perror("Erreur lors de l'écoute");
        exit(1);
    }
    
    printf("Serveur de jeu démarré sur le port %d\n", PORT);
    
    // Boucle principale du serveur
    while (1) {
        int new_socket;
        struct sockaddr_in client_addr;
        int addrlen = sizeof(client_addr);
        
        if ((new_socket = accept(server->socket_fd, (struct sockaddr *)&client_addr, (socklen_t*)&addrlen)) < 0) {
            perror("Erreur lors de l'accept");
            continue;
        }
        
        char buffer[BUFFER_SIZE] = {0};
        read(new_socket, buffer, BUFFER_SIZE);
        
        // Traitement du message reçu (supposé être un ID de joueur)
        int playerId = atoi(buffer);
        handleNewPlayer(server, playerId);
        
        close(new_socket);
    }
}

void handleNewPlayer(GameServer* server, int playerId) {
    addPlayer(server->players, playerId);
    printf("Nouveau joueur ajouté avec l'ID: %d\n", playerId);
}

void cleanupServer(GameServer* server) {
    close(server->socket_fd);
    freePlayerList(server->players);
    free(server);
} 