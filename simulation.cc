#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "constantes.h"
#include "simulation.h"
#include "message.h"
#include "shape.h"
#include "lifeform.h"

using namespace std;



//RENDU 2 À COMPLETER  

//void sauvegarde(char * nom_fichier);
//void execution();
//void dessin();

Simulation::Simulation(int nbr_al, int nbr_co, int nbr_sca)
        : nbr_algue(nbr_al), nbr_corail(nbr_co), nbr_scavenger(nbr_sca)
{}

bool Simulation::lecture(char * nom_fichier){

    string line;
    ifstream fichier(nom_fichier); 
    
    type = ALGUE;
    while(getline(fichier >> ws, line)) // ICI NE FONCTIONNE PLUS
    {   
        if(line[0]=='#' || line[0]=='\n' || line[0]=='\r') continue; 
        
        if(!decodage_ligne(line)) return false;
    }

    cout << message::success();

    return true;
}

bool Simulation::decodage_ligne(string line){
    bool decodage_ok = true;
    switch(type){
        case ALGUE:
            decodage_ok = decodage_algue(line);
            if (!decodage_ok){
                return false;
            } 
            break;

        case CORAIL:
            decodage_ok = decodage_corail(line);
            if (!decodage_ok) return false;
            break;

        case SCAVENGER:
            decodage_ok = decodage_scavenger(line);
            if (!decodage_ok) return false;
            break;
    } 
    return true;
}

bool Simulation::decodage_algue(string line){
    istringstream data(line);
    double x, y;
    int age;

    if(nbr_algue == 0){
        data >> nbr_algue;
    }
    else if(algue_vect.size() <= nbr_algue){
        data >> x >> y;
        if(!appartenance_recipient(x, y)) {
            return false;}
        data >> age;
        if(!age_positif(age)) return false;
        algue_vect.push_back(Algue(x, y, age));
    }   
    if(algue_vect.size() == nbr_algue){
        type = CORAIL;
        }

    return true;
}

bool Simulation::decodage_corail(string line){
    istringstream data(line);
    double x, y, a;
    int age;
    bool statut, dir_rot, statut_dev;
    unsigned int nbr_segments, id, s;

    if(nbr_corail == 0){
        data >> nbr_corail;
    }
    else if((corail_vect.size() != 0) && 
        (corail_vect.back().get_seg_vector().size() 
            < corail_vect.back().get_nbr_segments())){

        data >> a;
        if(!verifie_angle(a, corail_vect.back().get_id())) return false;
        data >> s;
        if(!longueur_segment(s, corail_vect.back().get_id())) return false;
        if(!extr_appartenance_recipient(x, y, s, a, id)) return false;
        corail_vect.back().add_seg_vector(a,s);   
        if(!seg_superposition()) return false;
        if(!collision()) return false;
    }
    else if(corail_vect.size() < nbr_corail){
        data >> x >> y;
        
        if(!appartenance_recipient(x, y)) return false;
        data >> age;
        if(!age_positif(age)) return false;
        data >> id;
        if(!unique_id(id)) return false;
        data >> statut >> dir_rot >> statut_dev >> nbr_segments;
        if(!verifie_positive(nbr_segments)) return false;
        corail_vect.push_back(
            Corail(x, y, age, id, statut, dir_rot, statut_dev, nbr_segments));

    }
    if((corail_vect.size() == nbr_corail) 
        && (corail_vect.back().get_seg_vector().size() 
            == corail_vect.back().get_nbr_segments())){
        type = SCAVENGER;
    }
    return true;
}

bool Simulation::decodage_scavenger(string line){
    istringstream data(line);
    double x, y;
    unsigned int id_corail_cible;
    unsigned int rayon;
    int age;
    bool statut;
    
    if(nbr_scavenger == 0){
        data >> nbr_scavenger;

    }
    else if(scavenger_vect.size() < nbr_scavenger){
        data >> x >> y;
        if(!appartenance_recipient(x, y)) return false;
        data >> age;
        if(!age_positif(age)) return false;
        data >> rayon;
        if(!rayon_scavenger(rayon)) return false;
        data >> statut;
        scavenger_vect.push_back(Scavenger(x, y, age, rayon, statut));

        if(statut == 1){
            if(data >> id_corail_cible){
                if(!existant_id(id_corail_cible)) return false;
            }
            scavenger_vect.back().init_corail_id_cible(id_corail_cible);
        } 
    }
    return true;
}

bool Simulation::appartenance_recipient(double x, double y){
    if((x < 1) || (y < 1) || (x > maximum-1) || (y > maximum-1)){
        cout << message::lifeform_center_outside(x, y);
        return false;
    }
    return true;
}


bool Simulation::extr_appartenance_recipient(double x, double y, 
    unsigned int s, double a, unsigned int id){

    x = x + s*cos(a);
    y = y + s*sin(a);

    if((x <= epsil_zero) || (x >= maximum - epsil_zero) || (y <= epsil_zero) || 
        (y >= maximum - epsil_zero)){
        cout << message::lifeform_computed_outside(id, x, y); 
        return false;
    }
    return true;
}

bool Simulation::unique_id(unsigned int id){
    for(size_t i(0); i < corail_vect.size(); i++){
        if(id == corail_vect[i].get_id()){
            cout << message::lifeform_duplicated_id(id);
            return false;
        }
    }
    return true;
}

bool Simulation::existant_id(unsigned int id_corail_cible){
    bool existant_id(false);
    
    for(size_t i(0); i < corail_vect.size(); i++){
        if(id_corail_cible == corail_vect[i].get_id()){
            existant_id = true;
        }
    }
    if(existant_id == false){
        cout << message::lifeform_invalid_id(id_corail_cible);
        return false;
    }
    return true;
}


bool Simulation::seg_superposition(){
    bool col(false);
    vector<Segments> seg_vector = corail_vect.back().get_seg_vector();
    unsigned int s1(seg_vector.size()-1);
    unsigned int s2(s1-1);
    Segments s = seg_vector.back();
    
    if(seg_vector.size() >= 2){ 
        col = s.superposition(seg_vector[seg_vector.size() - 2]);
    }
    if(col == 1){
        cout << message::segment_superposition(corail_vect.back().get_id(), 
            s2, s1);
        return false;
    }

    return true;
}


bool Simulation::collision(){
    bool col(false);
    
    vector<Segments> seg1_vector = corail_vect.back().get_seg_vector();

    S2d coord1 = corail_vect.back().get_coord();
    S2d extr1 = seg1_vector.back().get_extr();
    
    for(size_t i(0); i < corail_vect.size(); i++){
        S2d coord2 = corail_vect[i].get_coord();
        
        vector<Segments> seg2_vector = corail_vect[i].get_seg_vector();
        
        for(size_t j(0); j < seg2_vector.size(); j++){

            if((i == corail_vect.size()-1) && (j == seg2_vector.size()-1)){
                continue ;
            }
            if((i == corail_vect.size()-1) && (j == seg2_vector.size()-2)){
                continue ;
            }
            if((i == corail_vect.size()-1) && (j == seg2_vector.size())){
                continue ;
            }

            S2d extr2 = seg2_vector[j].get_extr();
            col = do_intersect(0, coord1, extr1, coord2, extr2);

            if(col == true){
                cout << message::segment_collision(corail_vect.back().get_id(), 
                    seg1_vector.size()-1, corail_vect[i].get_id(), j);
                
                return false;
            }
        }
    }
    return true;
}





