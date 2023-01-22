#ifndef GLOBAL_H
#define GLOBAL_H

#include <sys/poll.h>
#include <string>
#include <vector>
#include <set>
#include <chrono>

#define MAX_PLAYERS_PER_TEAM 32
#define PORT 8090
#define MAX_USERS 64;
//extern const int PORT;
//extern const int MAX_USERS;

extern int serverSock;
extern pollfd letterPollRed[MAX_PLAYERS_PER_TEAM];
extern pollfd letterPollBlu[MAX_PLAYERS_PER_TEAM];
extern int letterPollCountRed;
extern int letterPollCountBlu;
extern bool startedGame;
extern std::string phrase;

extern std::set<char> lettersLeftBlu;
extern std::vector<char> lettersGuessedBlu;
extern std::vector<char> lettersMissedBlu;

extern std::set<char> lettersLeftRed;
extern std::vector<char> lettersGuessedRed; //correct letters guessed
extern std::vector<char> lettersMissedRed;

extern std::vector<int> redPlayers;
extern std::vector<std::string> redNames;
extern std::vector<int> redPoints; // przy dodaniu gracza dodawać zero
extern int redRoundCounter;
extern std::vector<char> redGuesses;

extern std::vector<int> bluPlayers; //Descriptors for players
extern std::vector<std::string> bluNames; //Player names
extern std::vector<int> bluPoints; //Points for each player in the blue team
extern int bluRoundCounter;
extern std::vector<char> bluGuesses; //Votes from blue team

extern std::chrono::steady_clock::time_point redRoundStart;
extern std::chrono::steady_clock::time_point bluRoundStart;
//time till next vote

#endif