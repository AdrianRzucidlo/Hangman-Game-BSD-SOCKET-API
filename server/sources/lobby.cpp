#include "../headers/globalVariables.hh"
#include <unistd.h>

void lobbyTimer(){
    while(bluPlayers.empty() || redPlayers.empty()){
        sleep(15);
    }
}