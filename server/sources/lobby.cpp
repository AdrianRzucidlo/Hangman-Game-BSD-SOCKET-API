#include "../headers/globalVariables.hh"
#include <unistd.h>

void lobbyTimer(){
    while(bluPlayers.size() < 1 || redPlayers.size() < 1){
        sleep(15);
    }
}