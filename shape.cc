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
        void extr_init();

    private:
        S2d base;
        S2d extr;
        double angle;
        double longueur;
        double extr_x;
        double extr_y;
        vector<double> corails;
};

double Segments::get_angle(){
    return angle;
}

double Segments::get_longueur(){
    return longueur;
}

void Segments::extr_init(){
    extr_x = base.x + longueur*cos(angle);
    extr_y = base.y + longueur*sin(angle);

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


int main()
{
    struct Segments s;
    cin >> s.get_angle() >> s.get_longueur();
    if (!(-180 <= s.get_angle() <= 180))
    {
        cout << error; // à finir... message d'erreur avec module message
    }
     if (s.get_longueur < 0)
    {
        cout << error; // à finir... message d'erreur avec module message
    }


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


// TESTS ==============================