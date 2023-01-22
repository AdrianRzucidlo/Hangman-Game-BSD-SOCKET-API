#include <vector>
#include <set>
#include <chrono>
#include <unistd.h>
#include <iostream>
#include <sys/poll.h>
#include "../headers/globalVariables.hh"
#include <sys/socket.h>
#include <algorithm>
#include <errno.h>
#include <error.h>
#include <string>
#include <string.h>
void givePoint(int clientFd, char team){
    std::vector<int>& Players = (team=='r') ? redPlayers : bluPlayers;
    std::vector<int>& Points = (team=='r') ? redPoints : bluPoints;
    auto it = find(Players.begin(), Players.end(), clientFd);
    int index;
    if(it != Players.end()){
        int index = it - Players.begin();
    } else return;
    Points[index]++;
    return;
}

void letterPollEvent(int position, pollfd *letterPoll, int& letterPollCount, char team){
    int clientFd = letterPoll[position].fd;
    short int revents = letterPoll[position].revents;

    std::vector<char>& lettersGuessed = (team=='r') ? lettersGuessedRed : lettersGuessedBlu;
    std::set<char>& lettersLeft = (team=='r') ? lettersLeftRed : lettersLeftBlu;
    std::vector<char>& guesses = (team=='r') ? redGuesses : bluGuesses;
    std::chrono::steady_clock::time_point& roundStart = (team=='r') ? redRoundStart : bluRoundStart;
    if(revents & ~POLLIN){
        std::cout << "Removing player with fd=" << clientFd << std::endl;
        letterPoll[position] = letterPoll[letterPollCount-1];
        letterPollCount--;
        //usunac name i fd z listy!!!
        shutdown(clientFd, SHUT_RDWR);
        close(clientFd);
    }
    if(revents & POLLIN){
        char buffer[255];
        //MESSAGE
        int count = read(clientFd, buffer, 255);
        if(count < 1){
            revents |= POLLERR;
        }
        else {
            //    "115/L/"
            //sprawdzenie czasu
            //pobrać round z wiadomości i sprawdzić
            // std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
//MESSAGE
            // if(std::chrono::duration_cast<std::chrono::milliseconds>(now - roundStart).count() > 15000){
            //     auto ret = write(clientFd, "302;", 4); //Inform client of message too late
            //     if(ret==-1) error(1, errno, "write failed on descriptor %d", clientFd);
            //     if(ret!=4) error(0, errno, "wrote less than requested to descriptor %d (%ld/%d)", clientFd, ret, 4);
            //     return;
            // }
            

            //Get message, remove new line
            std::string letterMsg(buffer);
            letterMsg.erase(std::remove(letterMsg.begin(), letterMsg.end(), '\n'), letterMsg.cend());

            char ltr[1];
            strcpy(ltr,letterMsg.substr(4,1).c_str()); //Get letter
        
            *ltr = std::tolower(*ltr);
            std::cout << "Received letter " << *ltr << " from fd=" << clientFd << std::endl;

            guesses.push_back(*ltr); //Add letter to list of team guesses

            if(lettersLeft.find(*ltr) != lettersLeft.end()){ //If letter is correct give player a point
                givePoint(clientFd, team);
                //MESSAGE
                auto ret = write(clientFd, "201;", 4); //Inform client of correct guess
                if(ret==-1) error(1, errno, "write failed on descriptor %d", clientFd);
                if(ret!=4) error(0, errno, "wrote less than requested to descriptor %d (%ld/%d)", clientFd, ret, 4);
                return;
            }
            //MESSAGE
            auto ret = write(clientFd, "301;", 4); //Inform client of incorrect guess
            if(ret==-1) error(1, errno, "write failed on descriptor %d", clientFd);
            if(ret!=4) error(0, errno, "wrote less than requested to descriptor %d (%ld/%d)", clientFd, ret, 4);
            return;
        } 
    }
}