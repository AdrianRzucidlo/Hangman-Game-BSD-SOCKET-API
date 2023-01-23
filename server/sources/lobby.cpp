#include "../headers/globalVariables.hh"
#include <unistd.h>
#include <iostream>
void lobbyTimer(){
    while(bluPlayers.empty() || redPlayers.empty()){
        std::cout << "::Not enough players, waiting 15 seconds...\n";
        sleep(15);
    }
}