#ifndef GAME_SERVER_H
#define GAME_SERVER_H

#include "player.h"

#define PORT 8888
#define BUFFER_SIZE 1024

typedef struct {
    int socket_fd;
    PlayerList* players;
} GameServer;

GameServer* createServer(void);
void startServer(GameServer* server);
void handleNewPlayer(GameServer* server, int playerId);
void cleanupServer(GameServer* server);
void setupSignalHandler(GameServer* server);

#endif 