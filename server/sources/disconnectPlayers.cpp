#include <iostream>
#include "../headers/globalVariables.hh"
#include <sys/socket.h>
#include <unistd.h>

void disconnectPlayers(){
    std::cout << "::Disconnecting players\n";
    for(auto fd : bluPlayers){
        shutdown(fd, SHUT_RDWR);
        close(fd);
    }
    for(auto fd : redPlayers){
        shutdown(fd, SHUT_RDWR);
        close(fd);
    }
    std::cout << "::Clearing related data\n";
    bluPlayers.clear();
    redPlayers.clear();
    bluPoints.clear();
    redPoints.clear();
    bluNames.clear();
    redNames.clear();
    
    for(int i = 0; i < letterPollCountRed; ++i){
        letterPollRed[i].fd = 0;
        letterPollRed[i].revents = 0;
        letterPollRed[i].events = 0;
    }
    for(int i = 0; i < letterPollCountBlu; ++i){
        letterPollBlu[i].fd = 0;
        letterPollBlu[i].revents = 0;
        letterPollBlu[i].events = 0;
    }
    letterPollCountRed = 0;
    letterPollCountBlu = 0;
    std::cout << "::Finished\n";
    return;
}