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
bool stop = false;

const int PORT = 8090;
const int MAX_USERS = 10;
int serverSock;

std::vector<int> redPlayers;
std::vector<std::string> redNames;
std::vector<int> bluPlayers;
std::vector<std::string> bluNames;

void ctrl_c(int) {
    close(serverSock);
    exit(0);
}

void setReuseAddr(int socket){
    const int one = 1;
    int res = setsockopt(socket, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(one));
    if(res) error(1,errno, "setsockopt failed");
}


void createServer() {
    serverSock = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSock < 0)
    {
        std::cerr << "Error creating socket" << std::endl;
        exit(1);
    }
    setReuseAddr(serverSock);
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
    if(ret!=4) error(0, errno, "wrote less than requested to descriptor %d (%ld/%d)", playerFd, ret, 4);
    return;
}

void confirmName(int playerFd, bool accepted = true){
    if(accepted){
        auto ret = write(playerFd, "101;", 4);
        if(ret==-1) error(1, errno, "write failed on descriptor %d", playerFd);
        if(ret!=4) error(0, errno, "wrote less than requested to descriptor %d (%ld/%d)", playerFd, ret, 4);
        return;
    } else {
        auto ret = write(playerFd, "401;", 4);
        if(ret==-1) error(1, errno, "write failed on descriptor %d", playerFd);
        if(ret!=4) error(0, errno, "wrote less than requested to descriptor %d (%ld/%d)", playerFd, ret, 4);
        return;
    }
}

bool nameTaken(std::string name){
    for (int i = 0; i<redNames.size(); ++i){
        if(name.compare(redNames[i]) == 0) return true;
    }
    for (int i = 0; i<bluNames.size(); ++i){
        if(name.compare(bluNames[i]) == 0) return true;
    }
    return false;
}

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
                } else {
                    redPlayers.push_back(newPlayer);
                    redNames.push_back(name);
                }

                confirmName(newPlayer);
            }
        }
    }
}


int main()
{

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