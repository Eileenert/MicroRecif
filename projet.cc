#include <iostream>
#include "simulation.h"
using namespace std;

int main(int argc, char * argv[]){

    if(argc != 2){
        exit(EXIT_FAILURE);
    };

    Simulation s1;
    s1.lecture(argv[1]);
    return EXIT_SUCCESS; //surement a changer
}