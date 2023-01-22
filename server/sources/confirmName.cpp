#include <string>
#include <vector>
#include <error.h>
#include <unistd.h>

extern std::vector<std::string> redNames;
extern std::vector<std::string> bluNames;
void confirmName(int playerFd, bool accepted = true){
    if(accepted){
        //MESSAGE
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