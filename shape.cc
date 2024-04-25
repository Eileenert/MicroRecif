#define _USE_MATH_DEFINES
#include <iostream>
#include <vector>
#include <cmath>
#include "shape.h"
#include "graphic.h"
using namespace std;

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


bool Segments::superposition(Segments s){
    double ecart = ecart_angulaire(s);
    if (abs(ecart) <= 0) return true;
    return false;
}

double Segments::ecart_angulaire(Segments s){ 
    double ecart(0.);

    double v1(base.x - get_extr().x);
    double v2(base.y - get_extr().y);
    double u1(s.get_extr().x - s.get_base().x);
    double u2(s.get_extr().y -  s.get_base().y);
    double produit(v1*u1 + v2*u2);
    double prod_norm(longueur * s.get_longueur());
    double div(produit / prod_norm);

    if(div <= -1){
        ecart = acos(-1);
    }
    else if(div >= 1){
        ecart = acos(1);
    }
    else{
        ecart = acos(div);
    }

    return  ecart;
}

bool on_segment(bool simulation, S2d p, S2d q, S2d r){
    double s((r.x-p.x)*(q.x-p.x)+(r.y-p.y)*(q.y-p.y));
    double c(pow((r.x-p.x),2) + pow((r.y-p.y), 2)); 
    double pr(pow(c,1/2));
    double x(s/pr);

    if ((-epsil_zero*simulation <= x) && (x <= (pr + epsil_zero*simulation))) 
        return true; 
    return false; 
}

double orientation(S2d p, S2d q, S2d r){ 
    double val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y); 
    double norme = sqrt((pow((q.x - p.x), 2) + pow((q.y - p.y), 2)));
    double d = val/norme;

    if (abs(d) <= epsil_zero) return 0;
    
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

void dessin_algues(S2d coord){
    constexpr unsigned int r_alg(1) ; //j'avais la flemme d'appeler constantes.h juste pour ça et changer le makefile
    double x(coord.x);
    double y(coord.y);
    cercle(x, y, "algue", r_alg);
}

void dessin_trait(S2d base, S2d extr, bool is_alive){
    double x1(base.x);
    double y1(base.y);
    double x2(extr.x);
    double y2(extr.y);

    trait(x1, y1, x2, y2, is_alive);
}

void dessin_base_cor(S2d base, bool is_alive){
    double x(base.x);
    double y(base.y);
    
    carre_base_cor(x, y, is_alive);
}

void dessin_sca(S2d coord, unsigned int rayon){
    double x(coord.x);
    double y(coord.y);
    cercle(x, y, "scavenger", rayon);
}