#ifndef SIMULATION_H
#define SIMULATION_H
#include "lifeform.h"
#include <vector>
#include <string>


//3.1 il faut faire une classe simulation
class Simulation{
    public:
        Simulation(int nbr_al = 0, int nbr_co = 0, int nbr_sca = 0)
        : nbr_algue(nbr_al), nbr_corail(nbr_co), nbr_scavenger(nbr_sca)
        {}

        void lecture(char * nom_fichier);
        void decodage_ligne(std::string line);

        void decodage_algue(std::string line);
        void decodage_corail(std::string line);
        void decodage_scavenger(std::string line);

        void init_nbr_algue(int nbr);
        void init_nbr_corail(int nbr);
        void init_nbr_scavenger(int nbr);

        void appartenance_recipient(double x, double y);
        void extr_appartenance_recipient(double x, double y, unsigned int s, double a, unsigned int id);
        void unique_id(unsigned int id);
        void existant_id(unsigned int id_corail_cible);
        void seg_superposition();
        void collision();
        
    private:
        enum TYPE_lecture {ALGUE, CORAIL, SCAVENGER};
        int type;

        unsigned int nbr_algue;
        unsigned int nbr_corail;
        unsigned int nbr_scavenger;

        std::vector<Corail> corail_vect; 
        std::vector<Scavenger> scavenger_vect;
        std::vector<Algue> algue_vect;
};


#endif
