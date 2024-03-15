#include <iostream>
#include <string>
#include "message.h"
#include "shape.h"
using namespace std;

void verifie_angle();
void verifie_longueur();
void ecart_angulaire(double angle1, double angle2);//section 2.1

class Lifeform{
private:
    string type;
    int nbr_entite;
    int x;
    int y;
    int age;
};

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
};
Segments s;//INTERDIT PAR LES LOIS DE BOULIC!!!!!!!
void verifie_angle() {
    if (!(-180 <= s.get_angle() <= 180))
    {
        cout << message::segment_angle_outside; // à finir... message d'erreur avec module message
    }
};

void verifie_longueur(){
if (s.get_longueur() < 0)
    {
        cout << message::segment_length_outside; // à finir... message d'erreur avec module message
    }
};

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