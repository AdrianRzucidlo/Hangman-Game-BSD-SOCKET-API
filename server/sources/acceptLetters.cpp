#include <vector>
#include <sys/poll.h>
#include <errno.h>
#include <error.h>
#include "../headers/letterPollEvent.hh"
#include "../headers/globalVariables.hh"
#include <iostream>

void acceptLetters(char team){
    std::vector<int>& Players = (team=='r') ? redPlayers : bluPlayers;
    pollfd *letterPoll = (team=='r') ? letterPollRed : letterPollBlu;
    int& letterPollCount = (team=='r') ? letterPollCountRed : letterPollCountBlu;

    int playerCount = Players.size();

    for(int i = 0; i < playerCount; ++i){
        //semafor?
        letterPoll[i].fd=Players[i];
        letterPoll[i].events=POLLIN;
        letterPollCount++;
    }
    int ready;
    while(1){
        if(inLobby){
            return;
        }
        //dodać reakcję poll na serwerowy socket?
        std::cout << "[L]Polling...\n";
        ready = poll(letterPoll, letterPollCount, -1);
        if(inLobby){
            return;
        }
        if(ready == -1){
            error(0, errno, "poll failed");
        }
        std::cout << "[L]Event detected: " << ready << std::endl;
        for (int i = 0; i < letterPollCount && ready > 0; ++i){
            if(letterPoll[i].revents){
                letterPollEvent(i, letterPoll, letterPollCount, team);
                ready--;
            }
        }

    }

}