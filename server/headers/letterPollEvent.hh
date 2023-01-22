#ifndef LETTERPOLLEVENT_H
#define LETTERPOLLEVENT_H
#include <sys/poll.h>

void givePoint(int, char);
void letterPollEvent(int, pollfd*, int&, char);

#endif