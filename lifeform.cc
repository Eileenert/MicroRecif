#define _USE_MATH_DEFINES
#include <random> //section 3.1, util pour la gestion des probabilités
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
};


class Corail: public Lifeform{
    public:

    void verifie_angle(size_t index_segment);
    void verifie_longueur(size_t index_segment);
    void angle_segment(double& angle_seg, double base_x, double base_y,double extr_x, double extr_y);

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
    if(seg[index_segment].get_angle() < -M_PI || seg[index_segment].get_angle() > M_PI) {
        cout << message::segment_angle_outside;
        exit(EXIT_FAILURE); //Pour le rendu 1 seulement
    }
}

void Corail::verifie_longueur(size_t index_segment){
    if (seg[index_segment].get_longueur() < 0){
            cout << message::segment_length_outside;
            exit(EXIT_FAILURE); //Pour le rendu 1 seulement
        }
}

void Corail::angle_segment(double& angle_seg, double base_x, double base_y,double extr_x, double extr_y){ //trouve l'angle qu'un segment fait avec l'axe x, section 3.1
    extr_x = extr_x - base_x;
    extr_y = extr_y - base_y;

    angle_seg = atan2(extr_y, extr_x);
}//au cas où, je ne me suis pas trompée pour (y,x), c'est dans cette ordre ._. , est je crois qu'il faut entrer les coordonnées des extrémités
 //du segment et que ça part du principe que la base est à (0,0) pour la fonction atan2, alors j'ai recalculé 
 //les extrémités pour faire une translation des segments/vecteurs pour qu'ils aient leur base au point (0,0) pour le calcul de l'angle

void ecart_angulaire(double& ecart, double angle1, double angle2){ //section 2.1, angle1 c'est alphak et angle2 c'est alphak+1
    double ecart(0.);
    if (angle2 >= 0){
        ecart = M_PI - (angle2-angle1);
    }

    if (angle2 < 0){
        ecart = M_PI - (angle1+angle2); 
    }
}

bool bool_superpo(double ecart){
    double ecart(0.), a1(0.), a2(0.);
    bool superposition(0);

    ecart_angulaire(ecart, a1, a2);

    if (ecart == 0){
        superposition = 1;
    }

    return superposition;
}//section 2.1//shape à définir

//bool bool_intersect_superpo(){
//}//à finir ?? je sais pas si on doit faire ça aussi

bool onSegment(S2d p, S2d q, S2d r){
     //if (q.x <= max(p.x, r.x) && q.x >= min(p.x, r.x) && 
      //  q.y <= max(p.y, r.y) && q.y >= min(p.y, r.y)) 
    double s((r.x-p.x)*(q.x-p.x)+(r.y-p.y)*(q.y-p.y));
    double c(pow((r.x-p.x),2)+pow((r.y-p.y),2)); //c c'est le (X^2 + Y^2) du vecteur pr
    double pr(pow(c,1/2));// pr c'est la norme du vecteur pr
    double x(s/pr); //x c'est le truc que le prof veut qu'on calcul dans la section 2.2.2 (tkt on a pas besoin de comprendre exactement le pourquoi du calcul, c'est donné)

    if ((-epsil_zero <= x) && (x <= (pr+epsil_zero)))
        return true; 
  
    return false; 
}

int orientation(S2d p, S2d q, S2d r) 
{ 
    int val = (q.y - p.y) * (r.x - q.x) - 
              (q.x - p.x) * (r.y - q.y); 
  
    if (val == 0) return 0;
  
    return (val > 0)? 1: 2; 
}

bool doIntersect(S2d p1, S2d q1, S2d p2, S2d q2) 
{ 
    int o1 = orientation(p1, q1, p2); 
    int o2 = orientation(p1, q1, q2); 
    int o3 = orientation(p2, q2, p1); 
    int o4 = orientation(p2, q2, q1); 
  
    if (o1 != o2 && o3 != o4) 
        return true; 
  
    if (o1 == 0 && onSegment(p1, p2, q1)) return true; 
   
    if (o2 == 0 && onSegment(p1, q2, q1)) return true; 
   
    if (o3 == 0 && onSegment(p2, p1, q2)) return true; 
  
    if (o4 == 0 && onSegment(p2, q1, q2)) return true; 
  
    return false; 
} 
