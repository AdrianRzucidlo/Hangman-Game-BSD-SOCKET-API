#include <random>
#include <string>
#include <iostream>
#include <fstream>
#include <thread>
#include <unistd.h>

void thr(){
    int i = 0;
    while(i++ < 10){
        std::cout << "Działa\n";
        sleep(1);
    }
    return;
}

void a(){
    std::thread the(thr);
    the.detach();
    sleep(5);
    std::cout << "test\n";
    return;
}


int main(){
    
    a();
    while(1);
    
}