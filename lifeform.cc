#define _USE_MATH_DEFINES
#include <iostream>
#include <string>
#include <vector>
#include "message.h"
#include "lifeform.h"
#include "shape.h"
using namespace std;

Lifeform::Lifeform(double x1, double y1, int age1)
        :x(x1), y(y1), age(age1)
{}

S2d Lifeform::get_coord() const{
    S2d coord;
    coord.x = x;
    coord.y = y;
    return coord;
}
/*void Corail::angle_segment(double& angle_seg, double base_x, double base_y,
    double extr_x, double extr_y){
    extr_x = extr_x - base_x;
    extr_y = extr_y - base_y;
    angle_seg = atan2(extr_y, extr_x);
} //trouve l'angle qu'un segment fait avec l'axe x, section 3.1 */
Corail::Corail(double x1, double y1, int age1, unsigned int id1,
    bool statut_cor1, bool dir_rot1, bool statut_dev1, 
        unsigned int nbr_segments1)
:Lifeform(x1, y1, age1), id(id1), statut_cor(statut_cor1), dir_rot(dir_rot1), 
    statut_dev(statut_dev1), nbr_segments(nbr_segments1)
{}


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
    if(seg_vector.size() >=1){
        seg_vector.push_back(Segments(seg_vector.back().get_extr().x, 
            seg_vector.back().get_extr().y, a, s));
    }
    else{
        seg_vector.push_back(Segments(x, y, a, s));
    }  
}

Scavenger::Scavenger(double x1, double y1,int age1, unsigned int rayon1,
    bool statut_sca1)
:Lifeform(x1, y1, age1), rayon(rayon1), statut_sca(statut_sca1)
{}

void Scavenger::init_corail_id_cible(unsigned int corail_id_cible1){
    corail_id_cible = corail_id_cible1;
}