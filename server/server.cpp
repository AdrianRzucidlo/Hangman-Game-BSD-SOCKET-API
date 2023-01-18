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
bool stop = false;

const int PORT = 8080;
const int MAX_USERS = 10;
int serverSock;

std::vector<int> redPlayers;
std::vector<std::string> redNames;
std::vector<int> bluPlayers;
std::vector<std::string> bluNames;

void ctrl_c(int){
    // std::unique_lock<std::mutex> lock(clientFdsLock);
    // for(int clientFd : clientFds){
    //     shutdown(clientFd, SHUT_RDWR);
    //     close(clientFd);
    // }
    // close(servFd);
    // printf("Closing server\n");
    // exit(0);
}


void createServer() {
    serverSock = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSock < 0)
    {
        std::cerr << "Error creating socket" << std::endl;
        exit(1);
    }
    sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
    if (bind(serverSock, (sockaddr*)&address, sizeof(address)) < 0) {
        std::cerr << "Error binding socket to port" << std::endl;
        exit(1);
    }

    if (listen(serverSock, SOMAXCONN) < 0) 
    {
        std::cerr << "Error listening for connections" << std::endl;
        exit(1);
    }
}

void confirmConnection(int playerFd){
    auto ret = write(playerFd, "100;", 4);
    if(ret==-1) error(1, errno, "write failed on descriptor %d", playerFd);
    if(ret!=4) error(0, errno, "wrote less than requested to descriptor %d (%ld/%ld)", playerFd, ret, 4);
}

void newPlayerHandler(){
    pollfd playerPoll[1];
    playerPoll[0].fd = serverSock;
    playerPoll[0].events = POLLIN;
    while(1){
        int ready = poll(playerPoll, 1, -1);
        if(ready == -1){
            error(0, errno, "poll failed");
            //ctrl_c(SIGINT);  TODO Obsuga zakoczenia wszystkich threadow
        }

        if(playerPoll->revents){
            if(playerPoll->revents & ~POLLIN){
                error(0, errno, "Event %x on server socket", playerPoll->revents);
                //ctrl_c(SIGINT); TODO Obsuga zakoczenia wszystkich threadow
            }

            if(playerPoll->revents & POLLIN){
                char buffer[128];
                int newPlayer = accept(serverSock, NULL, NULL); //todo zapisac dane przychodzacego by wyswietlic w konsoli
                if(newPlayer == -1) error(1, errno, "accept failed");

                confirmConnection(newPlayer);
                //std::cout << "New connection from " << newPlayer
                int received = read(newPlayer, buffer, 128);
                if(received == -1) error(1,errno, "name read failed on descriptor %d", newPlayer);
                if(received <= 0){
                    shutdown(newPlayer, SHUT_RDWR);
                    close(newPlayer);
                    continue;
                }

                if(redPlayers.size()>=bluPlayers.size()) {
                    bluPlayers.push_back(newPlayer);
                    std::string name(buffer);
                    bluNames.push_back(name);
                } else {
                    redPlayers.push_back(newPlayer);
                    std::string name(buffer);
                    redNames.push_back(name);
                }
            }
        }
    }
}

void getPlayerName(int playerFd) {
    char buf[128];
}

int main()
{
    //signal(SIGINT, ctrl_c);
    //thread for handling connections with players
    std::thread playerAcceptingthread(newPlayerHandler);


    //int epoll_fd = epoll_create(MAX_EVENTS);
//     if(epoll_fd < 0) 
//     {
//     std::cerr << "Error creating epoll instance" << std::endl;
//     return 1;
//     }

//     epoll_event event;
//     event.events = EPOLLIN;
//     event.data.fd = serverSock;
//     if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, serverSock, &event) < 0) {
//     std::cerr << "Error adding listening socket to epoll instance" << std::endl;
//     return 1;
//   }
}