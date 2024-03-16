#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <string>
#include <vector>
#include "message.h"
#include "shape.h"
using namespace std;


void ecart_angulaire(double angle1, double angle2);//section 2.1

class Lifeform{

private:
    string type;
    int nbr_entite;
    int age;
};


class Corail{
    public:

    void verifie_angle(size_t index_segment);
    void verifie_longueur(size_t index_segment);

    private:
        
        //a voir si seg a besoin d'etre ordonne ou non pour appliquer les methodes du cours du 15/03/24
        vector<Segments> seg;// si j'ai bien compris un corail a plusieurs segments donc j'ai fait un vecteur

        /*dans le rapport 2.1.2 p.3 je crois qu'il veut des entiers mais je vais demander parce que
        bool est mieux que 0 ou 1 -_('')_- mais il nous donne aussi le nom de certaines variable et 
        peut-être que string c'est bien aussi, jsp a regarder
        */
        bool is_alive;
        bool is_extend; // true = EXTEND et false = REPRO
        string dir_rot;   //direction rotation (TRIGO) ou (INVTRIGO)
        string color; //bleu = alive ou noir = dead pour un prochain rendu, string parce que ensuite on devra surement mettre un code couleur rgb
        unsigned int nbr_segments;      //doit être strictement positif --> verifier dans une méthode à l'initialisation
        unsigned int cor_life_max; 
        
};

void Corail::verifie_angle(size_t index_segment) {
    if (!(-180 <= seg[index_segment].get_angle() <= 180)){
        cout << message::segment_angle_outside; // à finir... message d'erreur avec module message
    }
}

void Corail::verifie_longueur(size_t index_segment){
    if (seg[index_segment].get_longueur() < 0){
            cout << message::segment_length_outside; // à finir... message d'erreur avec module message
        }
}


void ecart_angulaire(double angle1, double angle2){ //section 2.1, angle1 c'est alphak et angle2 c'est alphak+1
    double ecart(0.);
    if (angle1 >= 0){
        ecart = M_PI - (angle2-angle1);
    }
    if (angle2 < 0){
        ecart = M_PI - (angle1-angle2);
    }
}



