#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "simulation.h"
#include "lifeform.h"


using namespace std;


//3.1 il faut faire une classe simulation
class Simulation{
    public:
        Simulation(int nbr_al = 0, int nbr_co=0, int nbr_sca=0)
        : nbr_algue(nbr_al), nbr_corail(nbr_co), nbr_scavenger(nbr_sca)
        {}

        void lecture(char * nom_fichier);
        void decodage_ligne(string line);

        void init_nbr_algue(int nbr);
        void init_nbr_corail(int nbr);
        void init_nbr_scavenger(int nbr);

        void verifie_positive(int nbr);

    private:
        enum TYPE_lecture {ALGUE, CORAIL, SCAVENGER};
        int type;

        int nbr_algue;
        int nbr_corail;
        int nbr_scavenger;
        
        vector<Corail> corail_vect;
        vector<Scavenger> scavenger_vect;
        vector<Algue> algue_vect;

};



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
        if(line[0]=='#' or line[0]=='\n' or line[0]=='\r')  continue; 
        decodage_ligne(line);

    }
    cout << "fin de la lecture" << endl;

}

void Simulation::decodage_ligne(string line){

    istringstream data(line);
    double x, y, id, rayon;
    int age;
    bool statut, dir_rot, statut_dev;
    unsigned int nbr_segments;


    switch(type){
        case ALGUE:
            if(nbr_algue == 0){
                data >> nbr_algue;

            }
            else if(algue_vect.size() <= nbr_algue){
                data >> x;
                data >> y;
                data >> age;
                algue_vect.push_back(Algue(x,y,age));
            }   

            if(algue_vect.size() == nbr_algue){
                type = CORAIL;
                }

            break;

        case CORAIL:
            if(nbr_corail == 0){
                    data >> nbr_corail;
                }
            //mettre une condition --> si on a un nbr de segment initialisé segments sinon la condition en dessous
            else if(corail_vect.size() <= nbr_corail){
                data >> x;
                data >> y;
                data >> age;
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

            break;

        case SCAVENGER:
            if(nbr_scavenger == 0){
                    data >> nbr_scavenger;

                }
                else if(algue_vect.size() <= nbr_algue){
                    data >> x;
                    data >> y;
                    data >> age;
                    data >> rayon;
                    data >> statut; //statut scavenger
                    data >> id; //id_corail_cible
                    scavenger_vect.push_back(Scavenger(x,y,age, rayon, statut, id));
                }   
            break;

    } 
}


//pour les tests
/*
int main(int argc, char * argv[]){
    Simulation s;
    s.lecture(argv[1]);
    return 0;
} */