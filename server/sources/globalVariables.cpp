#include <sys/poll.h>
#include <string>
#include <vector>
#include <set>
#include <chrono>
#include <random>

#define MAX_PLAYERS_PER_TEAM 32
#define MAX_USERS 64;

bool inLobby = true;
int serverSock;
pollfd letterPollRed[MAX_PLAYERS_PER_TEAM];
pollfd letterPollBlu[MAX_PLAYERS_PER_TEAM];
int letterPollCountRed = 0;
int letterPollCountBlu = 0;
bool startedGame = false;
std::string phrase;

std::set<char> lettersLeftBlu;
std::vector<char> lettersGuessedBlu;
std::vector<char> lettersMissedBlu;

std::set<char> lettersLeftRed;
std::vector<char> lettersGuessedRed;
std::vector<char> lettersMissedRed;

std::vector<int> redPlayers;
std::vector<std::string> redNames;
std::vector<int> redPoints; // przy dodaniu gracza dodawać zero
int redRoundCounter = 0;
std::vector<char> redGuesses;

std::vector<int> bluPlayers; //Descriptors for players
std::vector<std::string> bluNames; //Player names
std::vector<int> bluPoints; //Points for each player in the blue team
int bluRoundCounter = 0;
std::vector<char> bluGuesses; //Votes from blue team

std::chrono::steady_clock::time_point redRoundStart;
std::chrono::steady_clock::time_point bluRoundStart;
//time till next vote