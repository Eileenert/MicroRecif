#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "simulation.h"
#include "message.h"
#include "shape.h"
#include "lifeform.h"

using namespace std;

void verifie_positive(int nbr);
void age_positif(int age);
void longueur_segment(unsigned int s, unsigned int id);
void angle_segment(double a, unsigned int id);
void rayon_scavenger(unsigned int rayon);

void Simulation::init_nbr_algue(int nbr){
    verifie_positive(nbr);
    nbr_algue = nbr;
}
void Simulation::init_nbr_corail(int nbr){
    verifie_positive(nbr);
    nbr_corail = nbr;
}
void Simulation::init_nbr_scavenger(int nbr){
    verifie_positive(nbr);
    nbr_scavenger = nbr;
}

// traite le fichier ligne par ligne.  
void Simulation::lecture(char * nom_fichier){
    string line;
    ifstream fichier(nom_fichier); 

    type = ALGUE;
    // l’appel de getline filtre aussi les séparateurs
    while(getline(fichier >> ws, line)) 
    {
        // ligne de commentaire à ignorer, on passe à la suivante
        if(line[0]=='#' || line[0]=='\n' || line[0]=='\r') continue; 
        decodage_ligne(line);
    }
    cout << message::success();
}

void Simulation::decodage_ligne(string line){

    switch(type){
        case ALGUE:
            decodage_algue(line);
            break;

        case CORAIL:
            decodage_corail(line);
            break;

        case SCAVENGER:  
            decodage_scavenger(line);
            break;
    } 
}

void Simulation::decodage_algue(string line){
    istringstream data(line);
    double x, y;
    int age;

    if(nbr_algue == 0){
        data >> nbr_algue;

    }
    else if(algue_vect.size() <= nbr_algue){
        data >> x;
        data >> y;
        data >> age;
        age_positif(age);
        algue_vect.push_back(Algue(x,y,age));
    }   
    if(algue_vect.size() == nbr_algue){
        type = CORAIL;
        }
}

void Simulation::decodage_corail(string line){
    istringstream data(line);
    double x, y, a;
    int age;
    bool statut, dir_rot, statut_dev;
    unsigned int nbr_segments, id, s;

    if(nbr_corail == 0){
        data >> nbr_corail;
    }
    else if((corail_vect.size() != 0) && (corail_vect.back().get_seg_vector().size() < corail_vect.back().get_nbr_segments())){
        data >> a;
        angle_segment(a, corail_vect.back().get_id());
        data >> s;
        longueur_segment(s, corail_vect.back().get_id());
        corail_vect.back().add_seg_vector(a,s); 
        
    }
    else if(corail_vect.size() < nbr_corail){
        data >> x;
        data >> y;
        data >> age;
        age_positif(age);
        data >> id;
        unique_id(id);
        data >> statut; //statut corail
        data >> dir_rot;
        data >> statut_dev;
        data >> nbr_segments;
        corail_vect.push_back(Corail(x, y, age, id, statut, dir_rot, statut_dev, nbr_segments));
    }
    if((corail_vect.size() == nbr_corail) && (corail_vect.back().get_seg_vector().size() == corail_vect.back().get_nbr_segments())){
        type = SCAVENGER;
    }
}

void Simulation::decodage_scavenger(string line){
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
        
        data >> x;
        data >> y;
        data >> age;
        age_positif(age);
        data >> rayon;
        rayon_scavenger(rayon);
        data >> statut;
        scavenger_vect.push_back(Scavenger(x, y, age, rayon, statut));

        if(statut == 1){
            if(data >> id_corail_cible){
                existant_id(id_corail_cible);
            }
            scavenger_vect.back().init_corail_id_cible(id_corail_cible);
        } 
    } 
}

void Simulation::unique_id(unsigned int id){
    for(size_t i(0); i < corail_vect.size(); i++){
        if(id == corail_vect[i].get_id()){
            cout << message::lifeform_duplicated_id(id);
            exit(EXIT_FAILURE);
        }
    }
}

void Simulation::existant_id(unsigned int id_corail_cible){
    bool existant_id(false);
    
    for(size_t i(0); i < corail_vect.size(); i++){
        if(id_corail_cible == corail_vect[i].get_id()){
            existant_id = true;
        }
    }

    if(existant_id == false){
        cout << message::lifeform_invalid_id(id_corail_cible);
        exit(EXIT_FAILURE);
    }
}

void verifie_positive(int nbr){
    if(nbr <0){
        exit(EXIT_FAILURE);
    }
}

void age_positif(int age){
    if(age <= 0){
        cout << message::lifeform_age(age);
        exit(EXIT_FAILURE);
    }
}

void longueur_segment(unsigned int s, unsigned int id){
    constexpr unsigned l_repro (40) ;
    constexpr unsigned l_seg_interne (28) ;
    if ((s < (l_repro-l_seg_interne)) || (s >= l_repro)){
        cout << message::segment_length_outside(id, s);
        exit(EXIT_FAILURE);
    }    
}

void angle_segment(double a, unsigned int id){
    if((a < -M_PI) || (a > M_PI)){
        cout << message::segment_angle_outside(id,a);
        exit(EXIT_FAILURE);
    }
}

void rayon_scavenger(unsigned int rayon){
    constexpr unsigned r_sca(3) ;
    constexpr unsigned r_sca_repro(10) ;
    if ((rayon < r_sca) || (rayon > r_sca_repro)){
        cout << message::scavenger_radius_outside(rayon);
        exit(EXIT_FAILURE);
    } 
}

