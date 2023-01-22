#include <string>
#include <random>
#include <fstream>
#include <thread>
#include <unistd.h>
#include <errno.h>
#include <error.h>
#include "../headers/hangman.hh"
#include "../headers/globalVariables.hh"
#include <iostream>
#include <fstream>
std::string getAPhrase(std::uniform_int_distribution<> dist, std::mt19937 gen){
    
    int lineN = dist(gen);

    std::string line;
    std::ifstream file("./phrases.txt");
    if(!file){
        error(1, errno, "file");
        std::cout << "ERROR: Could not open phrases file, shutting down..\n";
        close(serverSock);
        exit(0);
    }
    for(int i = 0; i <= lineN; ++i){
        file >> line;
    }
    file.close();
    std::cout << ":::Generated phrase: " << line << std::endl;

    return line;
}

void roundEnd(char team, bool correct){
    std::vector<int>& Players = (team=='r') ? redPlayers : bluPlayers;
    std::vector<char>& lettersGuessed = (team=='r') ? lettersGuessedRed : lettersGuessedBlu;
    std::vector<char>& lettersMissed = (team=='r') ? lettersMissedRed : lettersMissedBlu;
    int& roundCounter = (team=='r') ? redRoundCounter : bluRoundCounter;
    std::string code;
    if(correct){
        code="202/";
    } else {
        code="302/";
    }
    std::string correctGuesses = "";
    for(auto c : lettersGuessed) correctGuesses+=c;
    if(!correctGuesses.compare("")) correctGuesses = "^";

    std::string incorrectGuesses = "";
    for(auto c : lettersMissed) incorrectGuesses+=c;
    if(!incorrectGuesses.compare("")) incorrectGuesses = "^";

    std::string msg(code+phrase+"/"+correctGuesses+"/"+incorrectGuesses+";");
    int msgSize = msg.size();
//MESSAGE
    for(auto fd : Players){
        auto ret = write(fd, msg.c_str(), msgSize);
        if(ret==-1) error(1, errno, "write failed on descriptor %d", fd);
        if(ret!=msgSize) error(0, errno, "wrote less than requested to descriptor %d (%ld/%d)", fd, ret, msgSize);
    }
    roundCounter++;
    return;
}

int mostVotes(int *alphabet){
    int idx = 0;
    int votes = -1;
    for(int i = 0; i < 26; ++i){
        if(alphabet[i] > votes){
            votes = alphabet[i];
            idx = i;
        }
    }
    if(votes==0) return -1;
    return idx;
}
void clearVotes(int* votes){
    for (int i = 0; i < 26; ++i) votes[i] = 0;
    return;
}

char hangman(std::uniform_int_distribution<> dist, std::mt19937 gen){
    std::cout << ":::Starting letter poll threads\n";
    std::thread playerLetterThreadRed(acceptLetters, 'r');
    std::thread playerLetterThreadBlu(acceptLetters, 'b');

    std::cout << ":::Generating secret phrase\n";
    phrase = getAPhrase(dist, gen);
    int len = phrase.length();

    int redAlphabet[26]; //+97 = a
    int bluAlphabet[26];
    int redHangman = 0;
    int bluHangman = 0;

    int redReceivedVotes = 0;
    int bluReceivedVotes = 0;

    int redMostVotedIdx = 0;
    int bluMostVotedIdx = 0;

    clearVotes(redAlphabet);
    clearVotes(bluAlphabet);

    for (int i = 0; i < len; ++i){
        lettersLeftBlu.insert(phrase[i]);
        lettersLeftRed.insert(phrase[i]);
    }

    informAboutStart();

    redRoundStart = std::chrono::steady_clock::now();
    bluRoundStart = redRoundStart;
    std::chrono::steady_clock::time_point currentTime = std::chrono::steady_clock::now();

    bluRoundCounter = 1;
    redRoundCounter = 1;
    while(redHangman < 8 && bluHangman < 8) {
        currentTime = std::chrono::steady_clock::now();
        while(!redGuesses.empty()) {
            char ltr = redGuesses[0];
            redGuesses.erase(redGuesses.begin());
            redAlphabet[ltr-97]++;
            redReceivedVotes++;
        }
        while(!bluGuesses.empty()) {
            char ltr = bluGuesses[0];
            bluGuesses.erase(bluGuesses.begin());
            bluAlphabet[ltr-97]++;
            bluReceivedVotes++;
        }

        redMostVotedIdx = mostVotes(redAlphabet);
        bluMostVotedIdx = mostVotes(bluAlphabet);
        if(redMostVotedIdx == -1){
            if(std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - redRoundStart).count() < 15000) continue;
        }
        if(std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - redRoundStart).count() >= 15000 || 
           redReceivedVotes == (int) redPlayers.size() || 
           redAlphabet[redMostVotedIdx] >= (int) redPlayers.size()){

            bool correct = false;
            char winningLetter = redMostVotedIdx+97;

            if(lettersLeftRed.find(winningLetter) != lettersLeftRed.end()){
                lettersLeftRed.erase(winningLetter);
                lettersGuessedRed.push_back(winningLetter);
                correct = true;
            } else {
                lettersMissedRed.push_back(winningLetter);
                redHangman++;
            }

            redReceivedVotes=0;
            redMostVotedIdx=0;
            
            clearVotes(redAlphabet);
            std::thread redRoundNext(roundEnd, 'r', correct);
            redRoundNext.detach();
            redRoundStart = std::chrono::steady_clock::now();
        }
        if(bluMostVotedIdx == -1){
            if(std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - bluRoundStart).count() < 15000) continue;
        }
        if(std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - bluRoundStart).count() >= 15000 || 
           bluReceivedVotes == (int) bluPlayers.size() ||
           bluAlphabet[bluMostVotedIdx] >= (int) bluPlayers.size()){
            
            bool correct = false;
            char winningLetter = bluMostVotedIdx+97;
            if(lettersLeftBlu.find(winningLetter) != lettersLeftBlu.end()){
                lettersLeftBlu.erase(winningLetter);
                lettersGuessedBlu.push_back(winningLetter);
                correct = true;
            } else {
                lettersMissedBlu.push_back(winningLetter);
                bluHangman++;
            }

            bluReceivedVotes=0;
            bluMostVotedIdx=0;
            clearVotes(bluAlphabet);
            std::thread bluRoundNext(roundEnd, 'b', correct);
            bluRoundNext.detach();
            bluRoundStart = std::chrono::steady_clock::now();
        }
    }
    if(redHangman >= 8) return 'b';
    else return 'r';
   

}