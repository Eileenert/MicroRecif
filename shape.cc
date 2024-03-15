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


void ecart_angulaire(double angle1, double angle2);//section 2.1
void bool_superpo();//section 2.1
void bool_intersect_superpo();//section 2.2


int main(){


    return 0; 
}

void ecart_angulaire(double angle1, double angle2){ //section 2.1, angle1 c'est alphak et angle2 c'est alphak+1
    double ecart(0.);
    if (angle1 >= 0)
    {
        ecart = 180 - (angle2-angle1);
    }
    if (angle2 < 0)
    {
        ecart = 180 - (angle1-angle2);
    }
}


// TESTS ==============================