#include <iostream>
#include <cmath>
#include <vector>
#include "message.h"
#include "shape.h"
using namespace std;

constexpr double epsil_zero(0.5) ;

double Segments::get_angle(){
    return angle;
}

double Segments::get_longueur(){
    return longueur;
}

S2d Segments::get_extr(){
    S2d extr;
    extr.x = base.x + longueur*cos(angle);
    extr.y = base.y + longueur*sin(angle);
    return extr;
}

void bool_superpo(){

}//section 2.1//shape à définir

void bool_intersect_superpo(){
}

// fonction que le prof veut qu'on fasse explicitement (dans shape ??) 
void orientation(){

}//section 2.2.1

void onSegment(){

}// détection d'appartenance d'un point q à un segment pr (q,p,r sont des points) section 2.2.2

void doIntersection(){

}//donne le résultat final sur la présence d'une intersection ou d'un alignement 

// TESTS ==============================