#ifndef NEWPLAYERHANDLER_H
#define NEWPLAYERHANDLER_H

#include<string>

void newPlayerHandler();
bool nameTaken(std::string);
void confirmName(int, char, bool = true);
void confirmConnection(int);

#endif