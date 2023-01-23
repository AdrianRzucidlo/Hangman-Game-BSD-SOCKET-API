#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/epoll.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <error.h>
#include <vector>
#include <thread>
#include <string>
#include <signal.h>
#include <sys/poll.h> 
#include <netdb.h>
#include <arpa/inet.h>
#include <algorithm>
#include "../headers/newPlayerHandler.hh"
#include "../headers/createServer.hh"
#include "../headers/lobby.hh"
#include "../headers/hangman.hh"
#include "../headers/globalVariables.hh"
#include "../headers/announceWinner.hh"
#include <random>
#include <fstream>
#include <set>
#include <chrono>

//bool stop = false;

void ctrl_c(int) {
    close(serverSock);
    exit(0);
}

int main()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(0, 212);

    signal(SIGINT, ctrl_c);
    std::cout << "Initializing server...\n";
    createServer();
    std::cout << "Server created\n";
    std::cout << "Running connection handling thread...\n";
    std::thread playerAcceptingthread(newPlayerHandler);
    
    for(int i = 0; i < MAX_PLAYERS_PER_TEAM; ++i){
        letterPollRed[i].revents = 0;
        letterPollBlu[i].revents = 0;
    }

    while(1){
        std::cout << "Entering lobby...\n";
        lobbyTimer();
        std::cout << "Starting game...\n";
        char winner = hangman(distr, gen);
        (winner=='r') ? std::cout << "==Winning team: Red==\n" : std::cout << "==Winning team: Blue==\n";
        std::cout << "Announcing to players...\n";
        announceWinner(winner);
        std::cout << "Game loop finished, pausing game thread for 10 seconds\n\n";
        sleep(10);
    }

}