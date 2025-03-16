#ifndef PLAYER_H
#define PLAYER_H

typedef struct {
    int id;
    char* name;
    // Autres informations du joueur à ajouter plus tard
} Player;

typedef struct {
    Player* players;
    int capacity;
    int capacityUpgrade;
    int count;
} PlayerList;

PlayerList* createPlayerList(int initialCapacity, int initialCapacityUpgrade);
void addPlayer(PlayerList* list, int playerId, char* playerName);
void removePlayer(PlayerList* list, int playerId);
void freePlayerList(PlayerList* list);

#endif 