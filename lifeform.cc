/* lifeform.cc
Orjowane Kaki 50%
Eileen Rheinboldt-Tran 50%
*/
#include <cmath>
#include <iostream>
#include <string>
#include <vector>
#include "message.h"
#include "lifeform.h"
#include "shape.h"
#include "constantes.h"

using namespace std;

Lifeform::Lifeform(double x1, double y1, unsigned int age1)
:x(x1), y(y1), age(age1)
{}

S2d Lifeform::get_coord() const
{
    S2d coord;
    coord.x = x;
    coord.y = y;
    return coord;
}

void Lifeform::set_coord(double x_set, double y_set)
{
    x = x_set;
    y = y_set;
}

unsigned int Lifeform::get_age() const
{
    return age;
}

void Lifeform::older()
{
    age +=1;
}

Algue::Algue(double x1, double y1, unsigned int age1)
    :Lifeform(x1, y1, age1)
{}

Corail::Corail(double x1, double y1, int age1, unsigned int id1,
    bool statut_cor1, bool dir_rot1, bool statut_dev1, 
        unsigned int nbr_segments1)
    :Lifeform(x1, y1, age1), id(id1), statut_cor(statut_cor1), dir_rot(dir_rot1)
    , statut_dev(statut_dev1), nbr_segments(nbr_segments1)
{}


vector<Segments>* Corail::get_seg_vector() 
{
    return &seg_vector;
}

unsigned int Corail::get_nbr_segments() const
{
    return nbr_segments;
}

void Corail::remove_last_segment(){
    seg_vector.pop_back();
    nbr_segments -= 1;
}

unsigned int Corail::get_id() const
{
    return id;
}

bool Corail::get_statut_cor() const
{
    return statut_cor;
}

bool Corail::get_dir_rot() const
{
    return dir_rot;
}

void Corail::set_dir_rot(){
    dir_rot = !dir_rot;
}

bool Corail::get_statut_dev() const
{
    return statut_dev;
}

void Corail::set_statut_dev(bool dev)
{
    statut_dev = dev;
}

bool Corail::get_is_alive() const
{
    return statut_cor;
}

void Corail::add_seg_vector(double a, int s)
{
    if(seg_vector.size() >=1){
        seg_vector.push_back(Segments(seg_vector.back().get_extr().x, 
            seg_vector.back().get_extr().y, a, s));
    }
    else{
        seg_vector.push_back(Segments(x, y, a, s));
    }  
    if(nbr_segments < seg_vector.size()){
        nbr_segments +=1;
    }   
}

void Corail::set_is_alive(bool alive){
    statut_cor = alive;
}

Scavenger::Scavenger(double x1, double y1,int age1, unsigned int rayon1,
    bool statut_sca1)
    :Lifeform(x1, y1, age1), rayon(rayon1), statut_sca(statut_sca1)
{}

void Scavenger::set_corail_id_cible(unsigned int corail_id_cible1) //j'ai changé init avce set
{
    corail_id_cible = corail_id_cible1;
}

unsigned int Scavenger::get_rayon() const
{
    return rayon;
}

bool Scavenger::get_statut_sca() const
{
    return statut_sca;
}

void Scavenger::set_statut_sca(bool a)
{
    statut_sca = a;
}


unsigned int Scavenger::get_corail_id_cible() const
{
   return corail_id_cible;
}

bool verifie_positive(int nbr)
{
    if(nbr <0){
        return false;
    }
    return true;
}

bool age_positif(int age)
{
    if(age <= 0){
        cout << message::lifeform_age(age);
        return false;
    }
    return true;
}

bool longueur_segment(unsigned int s, unsigned int id)
{
    if ((s < (l_repro-l_seg_interne)) || (s >= l_repro)){
        cout << message::segment_length_outside(id, s);
        return false;
    }   
    return true; 
}

bool verifie_angle(double a, unsigned int id)
{
    if((a < -M_PI) || (a > M_PI)){
        cout << message::segment_angle_outside(id,a);
        return false;
    }
    return true;
}

bool rayon_scavenger(unsigned int rayon)
{
    if ((rayon < r_sca) || (rayon >= r_sca_repro)){
        cout << message::scavenger_radius_outside(rayon);
        return false;
    } 
    return true;
}
