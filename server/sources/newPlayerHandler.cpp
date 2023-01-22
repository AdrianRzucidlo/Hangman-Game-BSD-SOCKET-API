#include <sys/poll.h>
#include <error.h>
#include <errno.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <string>
#include "../headers/newPlayerHandler.hh"
#include <iostream>
#include <arpa/inet.h>
#include <vector>
#include <algorithm>

extern int serverSock;

extern std::vector<int> redPlayers;
extern std::vector<std::string> redNames;
extern std::vector<int> redPoints;

extern std::vector<int> bluPlayers;
extern std::vector<std::string> bluNames;
extern std::vector<int> bluPoints;
//inform of curr round and  state
void newPlayerHandler(){
    pollfd playerPoll[1];
    playerPoll[0].fd = serverSock;
    playerPoll[0].events = POLLIN;
    while(1){
        int ready = poll(playerPoll, 1, -1);
        if(ready == -1){
            error(0, errno, "poll failed");
        }

        if(playerPoll->revents){
            if(playerPoll->revents & ~POLLIN){
                error(0, errno, "Event %x on server socket", playerPoll->revents);
            }

            if(playerPoll->revents & POLLIN){
                char buffer[128];
                sockaddr_in clientAddr{};
                socklen_t clientAddrSize = sizeof(clientAddr);

                int newPlayer = accept(serverSock, (sockaddr*) &clientAddr, &clientAddrSize);
                if(newPlayer == -1) error(1, errno, "accept failed");

                confirmConnection(newPlayer);

                std::cout << "New connection attempt from " << 
                inet_ntoa(clientAddr.sin_addr) <<":"<< 
                ntohs(clientAddr.sin_port) << "  FD: " << 
                newPlayer << std::endl;
                //MESSAGE
                int received = read(newPlayer, buffer, 128);
                if(received == -1) error(1,errno, "name read failed on descriptor %d", newPlayer);
                if(received <= 0){
                    shutdown(newPlayer, SHUT_RDWR);
                    close(newPlayer);
                    continue;
                }
                std::string name(buffer);
                name.erase(std::remove(name.begin(), name.end(), '\n'), name.cend());
                if(nameTaken(name)){
                    confirmName(newPlayer, false);
                    shutdown(newPlayer, SHUT_RDWR);
                    close(newPlayer);
                    continue;
                }

                if(redPlayers.size()>=bluPlayers.size()) {
                    bluPlayers.push_back(newPlayer);
                    bluNames.push_back(name);
                    bluPoints.push_back(0);
                } else {
                    redPlayers.push_back(newPlayer);
                    redNames.push_back(name);
                    redPoints.push_back(0);
                }

                confirmName(newPlayer);
            }
        }
    }
}