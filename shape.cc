#include <iostream>
#include <cmath>
#include "message.h"
using namespace std;

struct S2d {double x=0.; double y=0.;};
struct Segments
{
    struct S2d base;
    double angle;
    double longueur;
    struct S2d extr;
};
struct Carrés{};
struct Cercles{};

void ecart_angulaire(double angle1, double angle2);//section 2.1
void bool_superpo();//section 2.1
void bool_intersect_superpo();//section 2.2


int main()
{
    struct Segments s;
    cin >> s.angle >> s.longueur;
    if (!(-180 <= s.angle <= 180))
    {
        cout << error; // à finir... message d'erreur avec module message
    }
     if (s.longueur < 0)
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


