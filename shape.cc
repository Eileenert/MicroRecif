#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include <vector>
#include "shape.h"
using namespace std;

constexpr double epsil_zero(0.5);
void ecart_angulaire(double angle1, double angle2);//section 2.1
bool bool_superpo(double ecart);
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

void ecart_angulaire(double& ecart, double angle1, double angle2){ //section 2.1, angle1 c'est alphak et angle2 c'est alphak+1
    
    if (angle2 >= 0){
        ecart = M_PI - (angle2-angle1);
    }

    if (angle2 < 0){
        ecart = M_PI - (angle1+angle2); 
    }
}

bool bool_superpo(double ecart){
    double a1(0.), a2(0.);
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

double orientation(S2d p, S2d q, S2d r){ 
    double val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y); 
    double norme = pow((pow((q.x - p.x), 2) + pow((q.y - p.y), 2)), 1/2);
    double d = val/norme;

    if (abs(d) <= epsil_zero) 
        return 0;
  
    if (val == 0) 
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