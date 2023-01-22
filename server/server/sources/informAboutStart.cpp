#include<string>
#include<error.h>
#include<errno.h>
#include<unistd.h>
#include"../headers/globalVariables.hh"

void informAboutStart(){
    std::string msg("102/"+phrase+"/^/^;");
    int msgSize = msg.size();
    //MESSAGE
    for(long unsigned int i = 0; i < bluPlayers.size(); ++i){
        auto ret = write(bluPlayers[i], msg.c_str(), msgSize);
        if(ret==-1) error(1, errno, "write failed on descriptor %d", bluPlayers[i]);
        if(ret!=msgSize) error(0, errno, "wrote less than requested to descriptor %d (%ld/%d)", bluPlayers[i], ret, msgSize);
    }
    for(long unsigned int i = 0; i < redPlayers.size(); ++i){
        auto ret = write(redPlayers[i], msg.c_str(), msgSize);
        if(ret==-1) error(1, errno, "write failed on descriptor %d", redPlayers[i]);
        if(ret!=msgSize) error(0, errno, "wrote less than requested to descriptor %d (%ld/%d)", redPlayers[i], ret, msgSize);
    }
    
}