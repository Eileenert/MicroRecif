#define _USE_MATH_DEFINES
#include <iostream>
#include <vector>
#include <cmath>
#include "shape.h"
using namespace std;

constexpr double epsil_zero(0.5);
bool on_segment(bool simulation, S2d p, S2d q, S2d r);
double orientation(S2d p, S2d q, S2d r);

Segments::Segments(double x, double y, double a, unsigned int s)
        :angle(a), longueur(s)
        {
            S2d base_temp;
            base_temp.x = x;
            base_temp.y = y;
            base = base_temp;
        }


double Segments::get_angle() const{
    return angle;
}

double Segments::get_longueur() const{
    return longueur;
}

S2d Segments::get_extr() const{
    S2d extr;
    extr.x = base.x + longueur*cos(angle);
    extr.y = base.y + longueur*sin(angle);
    return extr;
}

S2d Segments::get_base() const{
    return base;
}


//en paramètre 1 segment à comparer avec le segment actuel (on met la fonction comme méthode de la classe segment)//
bool Segments::superposition(Segments s){
    double ecart = ecart_angulaire(s);
    if (abs(ecart) <= epsil_zero) return true;
    return false;
}


//calcul l'ecart angulaire entre l'angle du segment et celui du segment passé en paramètre
double Segments::ecart_angulaire(Segments s){ 

    double v1(get_extr().x - base.x);
    double v2(get_extr().y - base.y);
    double u1(s.get_extr().x - s.get_base().x);
    double u2(s.get_extr().x - s.get_base().x);
    double produit(v1*u1 + v2*u2);
    double prod_norm(longueur * s.get_longueur());

    return produit / prod_norm;
}


bool on_segment(bool simulation, S2d p, S2d q, S2d r){
    double s((r.x-p.x)*(q.x-p.x)+(r.y-p.y)*(q.y-p.y));
    double c(pow((r.x-p.x),2) + pow((r.y-p.y), 2)); //c c'est le (X^2 + Y^2) du vecteur pr
    double pr(pow(c,1/2));// pr c'est la norme du vecteur pr
    double x(s/pr); //x c'est le truc que le prof veut qu'on calcul dans la section 2.2.2 (tkt on a pas besoin de comprendre exactement le pourquoi du calcul, c'est donné)

    if ((-epsil_zero*simulation <= x) && (x <= (pr + epsil_zero*simulation))) 
        return true; 
    return false; 
}

double orientation(S2d p, S2d q, S2d r){ 

    double val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y); 
    double norme = sqrt((pow((q.x - p.x), 2) + pow((q.y - p.y), 2)));
    double d = val/norme;

    if (abs(d) <= epsil_zero){
        return 0;
    }
    return (val > 0)? 1: 2;
}

bool do_intersect(bool simulation, S2d p1, S2d q1, S2d p2, S2d q2){ 
   
    int o1 = orientation(p1, q1, p2); 
    int o2 = orientation(p1, q1, q2); 
    int o3 = orientation(p2, q2, p1); 
    int o4 = orientation(p2, q2, q1); 

    if (o1 != o2 && o3 != o4) return true; 


    if (o1 == 0 && on_segment(simulation, p1, p2, q1)) return true; 
   
    if (o2 == 0 && on_segment(simulation, p1, q2, q1)) return true; 
   
    if (o3 == 0 && on_segment(simulation,p2, p1, q2)) return true; 
  
    if (o4 == 0 && on_segment(simulation, p2, q1, q2)) return true; 
  
    return false; 
}

// TESTS ==============================