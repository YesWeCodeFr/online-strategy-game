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