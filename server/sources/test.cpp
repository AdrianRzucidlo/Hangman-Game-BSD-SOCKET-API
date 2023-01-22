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
#include <random>
#include <fstream>
#include <set>
#include <chrono>

int main(){
    auto currTime = std::time(nullptr);
    char * text = std::ctime(&currTime);
    char alphabet[26];
    for (int i = 0; i < 26; ++i) alphabet[i] = 97+i;
    for(int i = 0; i < 26; ++i) std::cout << alphabet[i];
 
    // std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    // sleep(5);
    // std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    // std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "[µs]" << std::endl;
    // std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count() << "[ns]" << std::endl;
}