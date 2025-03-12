[Retour vers le sommaire](sommaire.md)

# Création du projet serveur de jeu en C (12/03/2025)
## Prompt
```
J'aimerai maintenant créer le serveur de jeu. Pour l'instant ce serveur retient la liste des joueurs qui sont enregistrés. 
Contexte : 
- Le repository est un repository multi projets. Il contient actuellement le projet front-end et le projet back-end
- J'aimerai créer le projet du serveur de jeu en C, qui s'appelle game-server
- Ce projet reçoit des instructions depuis le back-end au travers de sockets.
- Pour l'instant, dès lors qu'un joueur est créé, lme back-end va appeler le serveur de jeu et lui indiquer l'id du joueur nouvellement créé.
- A la réception de la socket de création d'un joueur, l'id du joueur est stocké sur le serveur de jeu en mémoire dans un tableau de joueurs
```
## Réponse
Je vais vous aider à créer la structure de base du serveur de jeu en C. Je vais d'abord proposer une structure de dossiers puis le code initial.

1. Structure de dossiers proposée :
```
game-server/
├── src/
│   ├── main.c
│   ├── player.h
│   ├── player.c
│   ├── server.h
│   └── server.c
├── Makefile
└── .gitignore
```

2. Voici le code pour les différents fichiers :

game-server/src/player.h
```c
#ifndef PLAYER_H
#define PLAYER_H

typedef struct {
    int id;
    // Autres informations du joueur à ajouter plus tard
} Player;

typedef struct {
    Player* players;
    int capacity;
    int count;
} PlayerList;

PlayerList* createPlayerList(int initialCapacity);
void addPlayer(PlayerList* list, int playerId);
void removePlayer(PlayerList* list, int playerId);
void freePlayerList(PlayerList* list);

#endif
```

game-server/src/player.c
```c
#include <stdlib.h>
#include "player.h"

PlayerList* createPlayerList(int initialCapacity) {
    PlayerList* list = malloc(sizeof(PlayerList));
    list->players = malloc(sizeof(Player) * initialCapacity);
    list->capacity = initialCapacity;
    list->count = 0;
    return list;
}

void addPlayer(PlayerList* list, int playerId) {
    if (list->count >= list->capacity) {
        list->capacity *= 2;
        list->players = realloc(list->players, sizeof(Player) * list->capacity);
    }
    
    list->players[list->count].id = playerId;
    list->count++;
}

void removePlayer(PlayerList* list, int playerId) {
    for (int i = 0; i < list->count; i++) {
        if (list->players[i].id == playerId) {
            // Déplacer les éléments suivants
            for (int j = i; j < list->count - 1; j++) {
                list->players[j] = list->players[j + 1];
            }
            list->count--;
            break;
        }
    }
}

void freePlayerList(PlayerList* list) {
    free(list->players);
    free(list);
}
```

game-server/src/server.h
```c
#ifndef SERVER_H
#define SERVER_H

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

#endif
```

game-server/src/server.c
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "server.h"

GameServer* createServer(void) {
    GameServer* server = malloc(sizeof(GameServer));
    server->players = createPlayerList(10);
    
    // Création du socket
    server->socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server->socket_fd < 0) {
        perror("Erreur lors de la création du socket");
        exit(1);
    }
    
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
```

game-server/src/main.c
```c
#include <stdio.h>
#include "server.h"

int main() {
    GameServer* server = createServer();
    startServer(server);
    cleanupServer(server);
    return 0;
}
```

game-server/Makefile
```makefile
CC=gcc
CFLAGS=-Wall -Wextra
SRC_DIR=src
SRCS=$(wildcard $(SRC_DIR)/*.c)
OBJS=$(SRCS:.c=.o)
TARGET=game-server

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: clean
```

Ce code fournit :
1. Une gestion basique des joueurs avec une liste dynamique
2. Un serveur TCP simple qui écoute sur le port 8888
3. La capacité de recevoir des connexions et d'ajouter des joueurs

Pour utiliser ce serveur :
1. Créez les fichiers dans la structure indiquée
2. Compilez avec `make`
3. Exécutez avec `./game-server`

Le serveur attendra les connexions et stockera les IDs des joueurs reçus. Pour l'instant, il accepte simplement les connexions et stocke les IDs des joueurs. Vous pourrez ensuite étendre ses fonctionnalités selon vos besoins.

## Prompt
J'aimerai intercepter un évenement de fin de processus en appuyant sur les touches CTRL C

## Réponse

Je vais vous aider à gérer l'interruption SIGINT (CTRL+C) pour arrêter proprement le serveur. Voici les modifications nécessaires :

game-server/src/server.h
```c
// ... existing code ...

// Ajouter cette déclaration
void setupSignalHandler(GameServer* server);

// ... existing code ...
```

game-server/src/server.c
```c
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
    // ... existing code ...
    
    // Ajouter cette ligne avant le return
    setupSignalHandler(server);
    
    return server;
}

// ... existing code ...
```

game-server/src/main.c
```c:
#include <stdio.h>
#include "server.h"

int main() {
    printf("Démarrage du serveur de jeu (Appuyez sur CTRL+C pour quitter)\n");
    GameServer* server = createServer();
    startServer(server);
    // Cette ligne ne sera jamais atteinte en utilisation normale
    // car le serveur sera arrêté par CTRL+C
    cleanupServer(server);
    return 0;
}
```

Ces modifications permettent de :
1. Capturer le signal SIGINT (CTRL+C)
2. Nettoyer proprement les ressources du serveur avant de quitter
3. Afficher un message de fermeture

Maintenant, lorsque vous appuierez sur CTRL+C, le serveur se fermera proprement en libérant toutes les ressources allouées.

