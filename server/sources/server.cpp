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
    createServer();
    
    std::thread playerAcceptingthread(newPlayerHandler);

    std::cout << "test 1\n";
    while(1){
        std::cout << "==========\nRed players:\n";
        for(int i = 0; i < redPlayers.size(); i++) std::cout << redPlayers[i] <<" called " << redNames[i] << std::endl;
        std::cout << "Blu players:\n";
        for(int i = 0; i < bluPlayers.size(); i++) std::cout << bluPlayers[i] << " called " << bluNames[i] << std::endl;
        sleep(5);
    }
    
    while(1){
        lobbyTimer();

        hangman(distr, gen);
    }

}