#include <stdlib.h>
#include "player.h"

PlayerList* createPlayerList(int initialCapacity, int initialCapacityUpgrade) {
    PlayerList* list = malloc(sizeof(PlayerList));
    list->players = malloc(sizeof(Player) * initialCapacity);
    list->capacity = initialCapacity;
    list->capacityUpgrade = initialCapacityUpgrade;
    list->count = 0;
    return list;
}

void addPlayer(PlayerList* list, int playerId, char* playerName) {
    if (list->count >= list->capacity) {
        list->capacity += list->capacityUpgrade;
        list->players = realloc(list->players, sizeof(Player) * list->capacity);
    }
    Player* player = malloc(sizeof(Player));
    player->id = playerId;
    player->name = malloc(strlen(playerName) + 1);
    strcpy(player->name, playerName);
    list->players[list->count] = *player;
    list->count++;
}

void removePlayer(PlayerList* list, int playerId) {
    for (int i = 0; i < list->count; i++) {
        if (list->players[i].id == playerId) {
            freePlayer(&list->players[i]);
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
    if (list == NULL) return; // Vérifiez si la liste est NULL

    // Libérer la mémoire pour chaque joueur
    for (int i = 0; i < list->count; i++) {
        freePlayer(&list->players[i]);
    }
    free(list->players); // Libérer la mémoire pour le tableau de joueurs
    free(list); // Libérer la mémoire pour la structure PlayerList
} 

void freePlayer(Player* player) {
    // Libérer la mémoire pour le nom du joueur 
    free(player->name);
    // Libérer la mémoire pour le joueur
    free(player);
}