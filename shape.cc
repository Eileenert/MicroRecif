#include <iostream>
#include <cmath>
#include <vector>
#include "message.h"
using namespace std;

struct S2d {double x=0.; double y=0.;};

class Segments{
    public:
        double get_angle();
        double get_longueur();

        void init_angle();


    private:
        S2d base;
        double angle;
        double longueur;
        S2d extr;
        vector<double> corails;
};

double Segments::get_angle(){
    return angle;
}

double Segments::get_longueur(){
    return longueur;
}



struct Carres{
    vector<double> carres;
};
struct Cercles{
    vector<double> cercles;
};

void ecart_angulaire(double angle1, double angle2);//section 2.1
void bool_superpo();//section 2.1
void bool_intersect_superpo();//section 2.2
void verifie_angle();
void verifie_longueur();


int main()
{

    if (s.get_longueur() < 0)
    {
        cout << error; // à finir... message d'erreur avec module message
    }
    
    s.extr.x = s.base.x + s.longueur*cos(s.angle); //extr(x,y) coordonnées de l'extrémité du segment
    s.extr.y = s.base.y + s.longueur*sin(s.angle);


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
void bool_superpo();//section 2.1
void bool_intersect_superpo();//section 2.2

void verifie_angle() {
    struct Segments s;
    cin >> s.get_angle() >> s.get_longueur();
    if (!(-180 <= s.get_angle() <= 180))
    {
        cout << error; // à finir... message d'erreur avec module message
    }
};

void verifie_longueur(){
if (s.get_longueur() < 0)
    {
        cout << message::segment_length_outside; // à finir... message d'erreur avec module message
    }
}


