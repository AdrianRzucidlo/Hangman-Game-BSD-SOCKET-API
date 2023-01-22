#include <vector>
#include <sys/poll.h>
#include <errno.h>
#include <error.h>
#include "../headers/letterPollEvent.hh"
#include "../headers/globalVariables.hh"

void acceptLetters(char team){
    std::vector<int>& Players = (team=='r') ? redPlayers : bluPlayers;
    pollfd *letterPoll = (team=='r') ? letterPollRed : letterPollBlu;
    int& letterPollCount = (team=='r') ? letterPollCountRed : letterPollCountBlu;

    for(int i = 0; i < Players.size(); ++i){
        letterPoll[i].fd=Players[i];
        letterPoll[i].events=POLLIN;
        letterPollCount++;
    }
    int ready;
    while(1){
        ready = poll(letterPoll, letterPollCount, -1);

        if(ready == -1){
            error(0, errno, "poll failed");
        }

        for (int i = 0; i < letterPollCount && ready > 0; ++i){
            if(letterPoll[i].revents){
                letterPollEvent(i, letterPoll, letterPollCount, team);
                ready--;
            }
        }

    }

}