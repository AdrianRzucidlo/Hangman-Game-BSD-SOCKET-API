#ifndef HANGMAN_H
#define HANGMAN_H

#include <random>
#include <string>

std::string getAPhrase(std::uniform_int_distribution<>, std::mt19937);
char hangman(std::uniform_int_distribution<>, std::mt19937);
void informAboutStart();
void acceptLetters(char);

#endif