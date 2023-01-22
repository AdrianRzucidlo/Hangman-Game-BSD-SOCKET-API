#include <netinet/in.h>
#include <sys/socket.h>
#include <error.h>
#include <errno.h>
#include <iostream>
#include "../headers/globalVariables.hh"

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