#define _USE_MATH_DEFINES
//#include <random> //section 3.1, utile pour la gestion des probabilités, pas pour le rendu1
#include <cmath>
#include <iostream>
#include <string>
#include <vector>
#include "message.h"
#include "lifeform.h"
using namespace std;



/*void Corail::angle_segment(double& angle_seg, double base_x, double base_y,double extr_x, double extr_y){
    extr_x = extr_x - base_x;
    extr_y = extr_y - base_y;
    angle_seg = atan2(extr_y, extr_x);
} //trouve l'angle qu'un segment fait avec l'axe x, section 3.1 //pas utile pour l'instant*/

vector<Segments> Corail::get_seg_vector() const{
    return seg_vector;
}

unsigned int Corail::get_nbr_segments() const{
    return nbr_segments;
}

unsigned int Corail::get_id() const{
    return id;
}

void Corail::add_seg_vector(double a, int s){
    seg_vector.push_back(Segments(x, y, a, s));
}

void Scavenger::init_corail_id_cible(unsigned int corail_id_cible1){
    corail_id_cible = corail_id_cible1;
}