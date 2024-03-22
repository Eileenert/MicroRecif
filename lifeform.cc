#define _USE_MATH_DEFINES
#include <random> //section 3.1, util pour la gestion des probabilités
#include <cmath>
#include <iostream>
#include <string>
#include <vector>
#include "message.h"
#include "lifeform.h"
using namespace std;



void Corail::verifie_angle(size_t index_segment, unsigned id, double a){
    if(seg_vector[index_segment].get_angle() < -M_PI || seg_vector[index_segment].get_angle() > M_PI){
        cout << message::segment_angle_outside(id, a);
        exit(EXIT_FAILURE); //Pour le rendu 1 seulement
    }
}

void Corail::verifie_longueur(size_t index_segment, unsigned id, unsigned l){
    if (seg_vector[index_segment].get_longueur() < 0){
        cout << message::segment_length_outside(id, l);
        exit(EXIT_FAILURE); //Pour le rendu 1 seulement
    }
}

void Corail::angle_segment(/*size_t index_segment,*/ double& angle_seg, double base_x, double base_y,double extr_x, double extr_y){ //trouve l'angle qu'un segment fait avec l'axe x, section 3.1
    extr_x = extr_x - base_x;
    extr_y = extr_y - base_y;
    angle_seg = atan2(extr_y, extr_x);
    //seg_vector[index_segment].set_angle() = angle_seg;
}//je met une référence pour angle_seg ??
/////A CHANGER !!!

vector<Segments> Corail::get_seg_vector(){
    return seg_vector;
}

unsigned int Corail::get_nbr_segments(){
    return nbr_segments;
}

unsigned int Corail::get_id(){
    return id;
}

void Corail::add_seg_vector(double a, int s){
    seg_vector.push_back(Segments(x, y, a, s));
}

void Scavenger::init_corail_id_cible(unsigned int corail_id_cible1){
    corail_id_cible = corail_id_cible1;
}