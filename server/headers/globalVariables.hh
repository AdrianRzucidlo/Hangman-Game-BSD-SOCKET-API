#ifndef GLOBAL_H
#define GLOBAL_H

#include <sys/poll.h>
#include <string>
#include <vector>
#include <set>
#include <chrono>

#define MAX_PLAYERS_PER_TEAM 32
extern const int PORT = 8090;
extern const int MAX_USERS = 10;
extern int serverSock;
extern pollfd letterPollRed[MAX_PLAYERS_PER_TEAM];
extern pollfd letterPollBlu[MAX_PLAYERS_PER_TEAM];
extern int letterPollCountRed = 0;
extern int letterPollCountBlu = 0;
extern bool startedGame = false;
extern std::string phrase;

extern std::set<char> lettersLeftBlu;
extern std::vector<char> lettersGuessedBlu;

extern std::set<char> lettersLeftRed;
extern std::vector<char> lettersGuessedRed;

extern std::vector<int> redPlayers;
extern std::vector<std::string> redNames;
extern std::vector<int> redPoints; // przy dodaniu gracza dodawać zero
extern int redRoundCounter = 0;
extern std::vector<char> redGuesses;

extern std::vector<int> bluPlayers; //Descriptors for players
extern std::vector<std::string> bluNames; //Player names
extern std::vector<int> bluPoints; //Points for each player in the blue team
extern int bluRoundCounter = 0;
extern std::vector<char> bluGuesses; //Votes from blue team

extern std::chrono::steady_clock::time_point redRoundStart;
extern std::chrono::steady_clock::time_point bluRoundStart;
//time till next vote

#endif