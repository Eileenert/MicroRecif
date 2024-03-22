#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "simulation.h"
#include "message.h"
#include "shape.h"

using namespace std;

void age_positif(int age);

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

void Simulation::verifie_positive(int nbr){
    if(nbr <0){
        exit(EXIT_FAILURE);
    }
}

// traite le fichier ligne par ligne.  
void Simulation::lecture(char * nom_fichier)
{
    string line;
    ifstream fichier(nom_fichier); 

    type = ALGUE;
    // l’appel de getline filtre aussi les séparateurs
    while(getline(fichier >> ws, line)) 
    {
        // ligne de commentaire à ignorer, on passe à la suivante
        if(line[0]=='#' || line[0]=='\n' || line[0]=='\r')  continue; 
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
    double x, y, id, a;
    int age, s;
    bool statut, dir_rot, statut_dev;
    unsigned int nbr_segments;

    if(nbr_corail == 0){
        data >> nbr_corail;
    }
    else if((corail_vect.size() != 0) && (corail_vect.back().get_seg_vector().size() <= corail_vect.back().get_nbr_segments())){
        data >> s;
        data >> a;
        corail_vect.back().add_seg_vector(s,a); 
        
    }
    else if(corail_vect.size() <= nbr_corail){
        data >> x;
        data >> y;
        data >> age;
        age_positif(age);
        data >> id;
        data >> statut; //statut corail
        data >> dir_rot;
        data >> statut_dev;
        data >> nbr_segments;
        corail_vect.push_back(Corail(x, y, age, id, statut, dir_rot, statut_dev, nbr_segments));


    }
    if(corail_vect.size() == nbr_corail){
        type = SCAVENGER;
    }
}

void Simulation::decodage_scavenger(string line){
    istringstream data(line);
    double x, y, id_corail_cible, rayon;
    int age;
    bool statut;
    if(nbr_scavenger == 0){
        data >> nbr_scavenger;

    }
    else if(algue_vect.size() <= nbr_algue){
        data >> x;
        data >> y;
        data >> age;
        age_positif(age);
        data >> rayon;
        data >> statut;
        data >> id_corail_cible;
        scavenger_vect.push_back(Scavenger(x, y, age, rayon, statut, id_corail_cible));
    } 
}

void age_positif(int age){
    if(age <= 0){
        cout << message::lifeform_age(age);
        exit(EXIT_FAILURE);
    }
}

