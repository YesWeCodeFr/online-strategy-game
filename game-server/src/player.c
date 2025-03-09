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