#ifndef HANGMAN_H
#define HANGMAN_H

#include <random>
#include <string>

std::string getAPhrase(int);
char hangman(int);
void informAboutStart();
void acceptLetters(char);

#endif