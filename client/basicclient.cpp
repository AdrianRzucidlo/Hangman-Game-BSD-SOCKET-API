#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string>
#include <thread>

void receiveThread(int sockfd) {
    while (true) {
        char buffer[1024] = {0};
        int valread = read(sockfd, buffer, 1024);
        if (valread <=0) exit(0);
        if (valread > 0) {
            std::cout << "Received: " << buffer << std::endl;
        }
    }
}

int main() {
    // Create socket
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        std::cerr << "Failed to create socket" << std::endl;
        return 1;
    }

    // Server address
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr);

    // Connect to server
    if (connect(sockfd, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0) {
        std::cerr << "Failed to connect to server" << std::endl;
        return 1;
    }

    std::cout << "Connected to server" << std::endl;

    // Start receive thread
    std::thread receive_thread(receiveThread, sockfd);

    // Send data to server
    while (true) {
        std::string data;
        std::getline(std::cin, data);
        if (send(sockfd, data.c_str(), data.length(), 0) < 0) {
            std::cerr << "Failed to send data to server" << std::endl;
            return 1;
        }
    }

    // Close socket
    close(sockfd);

    return 0;
}