#include <unistd.h>
#include <error.h>
#include <errno.h>

void confirmConnection(int playerFd){
    //MESSAGE
    auto ret = write(playerFd, "100;", 4);
    if(ret==-1) error(1, errno, "write failed on descriptor %d", playerFd);
    if(ret!=4) error(0, errno, "wrote less than requested to descriptor %d (%ld/%d)", playerFd, ret, 4);
    return;
}