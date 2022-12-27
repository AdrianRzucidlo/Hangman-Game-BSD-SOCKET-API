#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/epoll.h>
#include <unistd.h>
#include <string.h>

const int PORT = 2137;
const int MAX_USERS = 10;

int main()
{
    int listen_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (listen_sock < 0)
    {
        std::cerr << "Error creating socket" << std::endl;
        return 1;
    }
    sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
    if (bind(listen_sock, (sockaddr*)&address, sizeof(address)) < 0) {
        std::cerr << "Error binding socket to port" << std::endl;
        return 1;
    }

    if (listen(listen_sock, MAX_USERS) < 0) 
    {
        std::cerr << "Error listening for connections" << std::endl;
        return 1;
    }

    int epoll_fd = epoll_create(MAX_EVENTS);
    if(epoll_fd < 0) 
    {
    std::cerr << "Error creating epoll instance" << std::endl;
    return 1;
    }

    epoll_event event;
    event.events = EPOLLIN;
    event.data.fd = listen_sock;
    if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, listen_sock, &event) < 0) {
    std::cerr << "Error adding listening socket to epoll instance" << std::endl;
    return 1;
  }
}