#include <string>
#include <random>
#include <fstream>
#include <thread>
#include "../headers/hangman.hh"
#include "../headers/globalVariables.hh"


std::string getAPhrase(std::uniform_int_distribution<> dist, std::mt19937 gen){
    std::ifstream file("phrases.txt");
    int lineN = dist(gen);
    std::string line;
    for(int i = 0; i <= lineN; ++i){
        std::getline(file, line);
    }
    file.close();
    return line;
}

void hangman(std::uniform_int_distribution<> dist, std::mt19937 gen){
    
    std::thread playerLetterThreadRed(acceptLetters, 'r');
    std::thread playerLetterThreadBlu(acceptLetters, 'b');

    phrase = getAPhrase(dist, gen);
    int len = phrase.length();
    char phraseChar[len];

    char alphabet[26];
    for (int i = 0; i < 26; ++i) alphabet[i] = 97+i;

    for (int i = 0; i < len; ++i){
        phraseChar[i]='_';
        lettersLeftBlu.insert(phrase[i]);
        lettersLeftRed.insert(phrase[i]);
    }

    informAboutStart();

    //czas i sprawdzanie liczby
    

}