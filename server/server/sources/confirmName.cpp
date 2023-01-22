#include <string>
#include <vector>
#include <error.h>
#include <unistd.h>
#include "../headers/globalVariables.hh"

void confirmName(int playerFd, char team, bool accepted = true){
    if(accepted){
        //MESSAGE

        if(inLobby){
            auto ret = write(playerFd, "101;", 4);
            if(ret==-1) error(1, errno, "write failed on descriptor %d", playerFd);
            if(ret!=4) error(0, errno, "wrote less than requested to descriptor %d (%ld/%d)", playerFd, ret, 4);
            return;
        }

        std::vector<char>& lettersGuessed = (team=='r') ? lettersGuessedRed : lettersGuessedBlu;
        std::vector<char>& lettersMissed = (team=='r') ? lettersMissedRed : lettersMissedBlu;

        std::string code="102/";
        
        std::string correctGuesses = "";
        for(auto c : lettersGuessed) correctGuesses+=c;
        if(!correctGuesses.compare("")) correctGuesses = "^";

        std::string incorrectGuesses = "";
        for(auto c : lettersMissed) incorrectGuesses+=c;
        if(!incorrectGuesses.compare("")) incorrectGuesses = "^";

        std::string msg(code+phrase+"/"+correctGuesses+"/"+incorrectGuesses+";");
        int msgSize = msg.size();



        auto ret = write(playerFd, msg.c_str(), msgSize);
        if(ret==-1) error(1, errno, "write failed on descriptor %d", playerFd);
        if(ret!=4) error(0, errno, "wrote less than requested to descriptor %d (%ld/%d)", playerFd, ret, msgSize);
        return;
    } else {
        auto ret = write(playerFd, "401;", 4);
        if(ret==-1) error(1, errno, "write failed on descriptor %d", playerFd);
        if(ret!=4) error(0, errno, "wrote less than requested to descriptor %d (%ld/%d)", playerFd, ret, 4);
        return;
    }
}

bool nameTaken(std::string name){
    for (long unsigned int i = 0; i<redNames.size(); ++i){
        if(name.compare(redNames[i]) == 0) return true;
    }
    for (long unsigned int i = 0; i<bluNames.size(); ++i){
        if(name.compare(bluNames[i]) == 0) return true;
    }
    return false;
}