#include "../headers/globalVariables.hh"
#include <string>
#include <unistd.h>
#include <errno.h>
#include <error.h>

void announceWinner(char winner){
    std::string code="500/";
    
    std::string bestFromWinners;
    std::string bestFromLosers;

    int maxRed = -1, maxBlu = -1;
    std::string bestRed, bestBlu;
    for(long unsigned int i = 0; i < redNames.size(); i++){
        if(redPoints[i] > maxRed){ 
            maxRed = redPoints[i];
            bestRed = redNames[i];
        }
    }
    for(long unsigned int i = 0; i < bluNames.size(); i++){
        if(bluPoints[i] > maxBlu){ 
            maxBlu = bluPoints[i];
            bestBlu = bluNames[i];
        }
    }
    bestFromWinners = (winner == 'r') ? bestRed + ":" + std::to_string(maxRed) : bestBlu + ":" + std::to_string(maxBlu);
    bestFromLosers = (winner == 'r') ? bestBlu + ":" + std::to_string(maxBlu) : bestRed + ":" + std::to_string(maxRed);
    std::string msg(code+phrase+"/"+
    bestFromWinners+"/"+
    bestFromLosers+";");
    int msgSize = msg.size();
    if(winner == 'b'){
        for(auto fd : redPlayers){
            auto ret = write(fd, msg.c_str(), msgSize);
            if(ret==-1) error(1, errno, "write failed on descriptor %d", fd);
            if(ret!=msgSize) error(0, errno, "wrote less than requested to descriptor %d (%ld/%d)", fd, ret, msgSize);
        }
        for(auto fd : bluPlayers){
            auto ret = write(fd, msg.c_str(), msgSize);
            if(ret==-1) error(1, errno, "write failed on descriptor %d", fd);
            if(ret!=msgSize) error(0, errno, "wrote less than requested to descriptor %d (%ld/%d)", fd, ret, msgSize);
        }
    } else {
        for(auto fd : bluPlayers){
            auto ret = write(fd, msg.c_str(), msgSize);
            if(ret==-1) error(1, errno, "write failed on descriptor %d", fd);
            if(ret!=msgSize) error(0, errno, "wrote less than requested to descriptor %d (%ld/%d)", fd, ret, msgSize);
        }
        for(auto fd : redPlayers){
            auto ret = write(fd, msg.c_str(), msgSize);
            if(ret==-1) error(1, errno, "write failed on descriptor %d", fd);
            if(ret!=msgSize) error(0, errno, "wrote less than requested to descriptor %d (%ld/%d)", fd, ret, msgSize);
        }
    }
}