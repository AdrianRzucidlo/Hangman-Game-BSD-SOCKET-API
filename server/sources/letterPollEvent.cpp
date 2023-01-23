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
    int index = 0;
    if(it != Players.end()){
        index = it - Players.begin();
    } else return;
    Points[index]+=1;
    return;
}

void letterPollEvent(int position, pollfd *letterPoll, int& letterPollCount, char team){
    int clientFd = letterPoll[position].fd;

    std::vector<int>& Players = (team=='r') ? redPlayers : bluPlayers;
    std::vector<int>& Points = (team=='r') ? redPoints : bluPoints;
    std::vector<std::string>& Names = (team=='r') ? redNames : bluNames;
    std::set<char>& lettersLeft = (team=='r') ? lettersLeftRed : lettersLeftBlu;
    std::vector<char>& guesses = (team=='r') ? redGuesses : bluGuesses;
    int& roundCounter = (team=='r') ? redRoundCounter : bluRoundCounter;

    std::cout << "[L]Revents value: " << letterPoll[position].revents << std::endl;

    if(letterPoll[position].revents & ~POLLIN){
        std::cout << "[L]Removing player with fd=" << clientFd << std::endl;
        letterPoll[position] = letterPoll[letterPollCount-1];
        letterPollCount--;
        auto it = find(Players.begin(), Players.end(), clientFd);
        if (it != Players.end()){
            int index = it - Players.begin();
            Players.erase(Players.begin()+index);
            Names.erase(Names.begin()+index);
            Points.erase(Points.begin()+index);
        }
        shutdown(clientFd, SHUT_RDWR);
        close(clientFd);
    }
    if(letterPoll[position].revents & POLLIN){
        char buffer[255];
        //MESSAGE
        int count = read(clientFd, buffer, 255);

        if(count < 1){
            std::cout << "[L]Error: Message shorter than 1\n";
            letterPoll[position].revents |= POLLERR;
        }
        else {
            std::string letterMsg(buffer);

            letterMsg.erase(std::remove(letterMsg.begin(), letterMsg.end(), '\n'), letterMsg.cend());
            letterMsg.erase(std::remove(letterMsg.begin(), letterMsg.end(), ';'), letterMsg.cend());
            if(letterMsg.substr(0,3).compare("115")) return;
            int round = std::stoi(letterMsg.substr(6));
            std::cout << "[L]Round received: " << round << " | Actual: " << roundCounter << std::endl;
            //MESSAGE
            
            if(round != roundCounter){
                std::vector<char>& lettersGuessed = (team=='r') ? lettersGuessedRed : lettersGuessedBlu;
                std::vector<char>& lettersMissed = (team=='r') ? lettersMissedRed : lettersMissedBlu;
                std::string code="402/";
                
                std::string correctGuesses = "";
                for(auto c : lettersGuessed) correctGuesses+=c;
                if(!correctGuesses.compare("")) correctGuesses = "^";

                std::string incorrectGuesses = "";
                for(auto c : lettersMissed) incorrectGuesses+=c;
                if(!incorrectGuesses.compare("")) incorrectGuesses = "^";

                std::string msg(code+phrase+"/"+correctGuesses+"/"+incorrectGuesses+";");
                int msgSize = msg.size();
                auto ret = write(clientFd, msg.c_str(), msgSize); //Inform client of message too late
                if(ret==-1) error(1, errno, "write failed on descriptor %d", clientFd);
                if(ret!=4) error(0, errno, "wrote less than requested to descriptor %d (%ld/%d)", clientFd, ret, msgSize);
                return;
            }

            char ltr[1];
            strcpy(ltr,letterMsg.substr(4,1).c_str()); //Get letter
            *ltr = std::tolower(*ltr);
            std::cout << "[L]Received letter " << *ltr << " from fd=" << clientFd << std::endl;

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