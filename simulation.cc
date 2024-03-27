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
        appartenance_recipient(x, y);
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
    else if((corail_vect.size() != 0) && 
            (corail_vect.back().get_seg_vector().size() 
                < corail_vect.back().get_nbr_segments())){
        data >> a;
        angle_segment(a, corail_vect.back().get_id());
        data >> s;
        longueur_segment(s, corail_vect.back().get_id());
        extr_appartenance_recipient(x, y, s, a, id);
        
        corail_vect.back().add_seg_vector(a,s);   
        seg_superposition();
        collision();
    }
    else if(corail_vect.size() < nbr_corail){
        data >> x;
        data >> y;
        appartenance_recipient(x, y);
        data >> age;
        age_positif(age);
        data >> id;
        unique_id(id);
        data >> statut; //statut corail
        data >> dir_rot;
        data >> statut_dev;
        data >> nbr_segments;
        corail_vect.push_back(Corail(x, y, age, id, statut, dir_rot, 
                                        statut_dev, nbr_segments));
        
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
        appartenance_recipient(x, y);
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

//section 3.2.2 du rendu1
void Simulation::appartenance_recipient(double x, double y){
    constexpr double max(256.);
    
    if((x < 1) || (y < 1) || (x > max-1) || (y > max-1)){ //verifie que les centres des algues, scavenger et la base des coraux sont dans le domaine
        cout << message::lifeform_center_outside(x, y);
        exit(EXIT_FAILURE);
    }
}

void Simulation::extr_appartenance_recipient(double x, double y,
         unsigned int s, double a, unsigned int id){
    constexpr double max(256.);
    constexpr double epsil_zero(0.5);

    x = x + s*cos(a);
    y = y + s*sin(a);

    if((x <= epsil_zero) || (x >= max - epsil_zero) || (y <= epsil_zero) || (y >= max - epsil_zero)){//vérifie pendant la simulation
        cout << message::lifeform_computed_outside(id, x, y); //je crois que c'est pas ce message d erreur, je pense que c'est le bon ._.
        exit(EXIT_FAILURE);
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


void Simulation::seg_superposition(){
    bool col(false);
    vector<Segments> seg_vector = corail_vect.back().get_seg_vector();
    unsigned int s1(seg_vector.size()-1); //s1 c'est le nombre d'éléments du vecteur - 1 ?
    unsigned int s2(s1-1);//s2 c'est le nombre d'éléments du vecteur ?
    Segments s = seg_vector.back();// accès au dernier élément
    
    if(seg_vector.size() >= 2){ //s'il y'a plus d'un segment dans le corail
        col = s.superposition(seg_vector[seg_vector.size() - 2]);//vérification en mode lecture// col = true superposition
    }
    if(col == 1){
        cout << message::segment_superposition(corail_vect.back().get_id(), s2, s1);
        exit(EXIT_FAILURE);
    }
}//donc tous ça fait qu'en mode lecture on sait si y'a une superposition

//jsp si c'est correct
//NE PAS COMPARER AVEC LES SEGMENTS A COTE
void Simulation::collision(){
    bool col(false);
    
    vector<Segments> seg1_vector = corail_vect.back().get_seg_vector();

    S2d coord1 = corail_vect.back().get_coord();
    S2d extr1 = seg1_vector.back().get_extr();
    
    for(size_t i(0); i < corail_vect.size(); i++){
        S2d coord2 = corail_vect[i].get_coord();
        vector<Segments> seg2_vector = corail_vect[i].get_seg_vector();
        
        for(size_t j(0); j < seg2_vector.size(); j++){

            if((i == corail_vect.size()-1) && (j == seg2_vector.size()-1)) continue ;
            if((i == corail_vect.size()-1) && (j == seg2_vector.size()-2)) continue ;
            if((i == corail_vect.size()-1) && (j == seg2_vector.size())) continue ;

            S2d extr2 = seg2_vector[j].get_extr();
            
            col = do_intersect(0, coord1, extr1, coord2, extr2);

            if(col == true){
                cout << message::segment_collision(corail_vect.back().get_id(), seg1_vector.size()-1,
                                        corail_vect[i].get_id(), j);  //changer valeur des deux derniers
                
                exit(EXIT_FAILURE);
            }
        }
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
    if ((rayon < r_sca) || (rayon >= r_sca_repro)){
        cout << message::scavenger_radius_outside(rayon);
        exit(EXIT_FAILURE);
    } 
}


