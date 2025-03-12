#include "game_server.h"
#include "network/server.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <signal.h>

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
    GameServer* server = (GameServer*)malloc(sizeof(GameServer));
    if (!server) {
        perror("Erreur d'allocation mémoire pour le serveur");
        return NULL;
    }
    
    server->players = createPlayerList(10);
    server->socket_fd = -1;
    
    return server;
}

void startServer(GameServer* server) {
    // Initialiser le socket du serveur
    server->socket_fd = init_server(PORT);
    if (server->socket_fd < 0) {
        fprintf(stderr, "Échec de l'initialisation du serveur\n");
        return;
    }
    
    printf("Serveur de jeu démarré sur le port %d\n", PORT);
    
    // Démarrer la boucle d'écoute
    start_server_loop(server->socket_fd);
}

void handleNewPlayer(GameServer* server, int playerId) {
    addPlayer(server->players, playerId);
    printf("Nouveau joueur ajouté, id: %d\n", playerId);
}

void cleanupServer(GameServer* server) {
    if (server) {
        // Fermer le socket
        if (server->socket_fd >= 0) {
            stop_server(server->socket_fd);
        }
        
        // Libérer la liste des joueurs
        freePlayerList(server->players);
        
        // Libérer la structure du serveur
        free(server);
        
        printf("Ressources du serveur libérées\n");
    }
} 