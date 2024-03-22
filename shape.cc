#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include <vector>
#include "shape.h"
using namespace std;

constexpr double epsil_zero(0.5);
void ecart_angulaire(double& ecart, double angle1, double angle2);//section 2.1
bool onSegment(S2d p, S2d q, S2d r);
double orientation(S2d p, S2d q, S2d r);
bool doIntersect(S2d p1, S2d q1, S2d p2, S2d q2);

Segments::Segments(double x, double y, double a, unsigned s)
        :angle(a), longueur(s)
        {
            S2d base_temp;
            base_temp.x = x;
            base_temp.y = y;
            base = base_temp;
        }


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

void ecart_angulaire(double& ecart, double angle1, double angle2){ //calcul l'ecart angulaire entre deux segments 
    
    if (angle2 >= 0){
        ecart = M_PI - (angle2-angle1);
    }

    if (angle2 < 0){
        ecart = M_PI - (angle1+angle2); 
    }
}

// en parametres 1 segment à comparé avec le segment actuel (on met la fonction comme méthode de la classe segment)
bool Segments::superposition(bool lecture, Segments s){//booléen lecture 1 = on est en lecture de fichier
    double a2 = s.get_angle();
    constexpr double delta_rot(0.0625);
    double ecart(0.);

    ecart_angulaire(ecart, angle, a2);//a2 c'est l'angle de la 2eme partie du segment qui partage la même extremitée

    if ((ecart == 0) && (lecture == 1)) //si l'ecart est nul en lecture de fichier il y'a superposition
        return true;
    if ((ecart >= -delta_rot) && (ecart <= delta_rot)) //s'il appartient à l'intervalle et change de signe lors de la mise à jour en simulation
        return true;

    return false;
}//section 2.1 et 3.2.3 true = superposition

bool onSegment(bool use_epsil, S2d p, S2d q, S2d r){
    double s((r.x-p.x)*(q.x-p.x)+(r.y-p.y)*(q.y-p.y));
    double c(pow((r.x-p.x),2)+pow((r.y-p.y),2)); //c c'est le (X^2 + Y^2) du vecteur pr
    double pr(pow(c,1/2));// pr c'est la norme du vecteur pr
    double x(s/pr); //x c'est le truc que le prof veut qu'on calcul dans la section 2.2.2 (tkt on a pas besoin de comprendre exactement le pourquoi du calcul, c'est donné)

    if ((-epsil_zero*use_epsil <= x) && (x <= (pr+use_epsil*epsil_zero)))
        return true; 
  
    return false; 
}

double orientation(S2d p, S2d q, S2d r){ 
    double val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y); 
    double norme = pow((pow((q.x - p.x), 2) + pow((q.y - p.y), 2)), 1/2);
    double d = val/norme;

    if (abs(d) <= epsil_zero) 
        return 0;

    return (val > 0)? 1: 2; //je garde cette ligne ?? question assistant
}

bool doIntersect(S2d p1, S2d q1, S2d p2, S2d q2){ 
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

// TESTS ==============================