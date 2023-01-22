#include <random>
#include <string>
#include <iostream>
#include <fstream>


int main(){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, 212);
    std::ifstream file("phrases.txt");
    int lineN = dist(gen);
    
    std::string line;
    for(int i = 0; i <= lineN; ++i){
        std::getline(file, line);
        std::cout << "::::::Phrase " << line << std::endl;
    }
    file.close();
    std::cout << ":::Generated phrase: " << line << std::endl;
}