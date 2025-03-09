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