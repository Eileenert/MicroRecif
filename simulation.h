#ifndef SIMULATION_H
#define SIMULATION_H
#include "lifeform.h"
#include <vector>
#include <string>


class Simulation{
    public:
        Simulation(int nbr_al = 0, int nbr_co = 0, int nbr_sca = 0);

        void sauvegarde(std::string nom_fichier);

        bool lecture(char * nom_fichier);
        bool decodage_ligne(std::string line);

        bool decodage_algue(std::string line);
        bool decodage_corail(std::string line);
        bool decodage_scavenger(std::string line);

        bool appartenance_recipient(double x, double y);
        bool extr_appartenance_recipient(double x, double y, unsigned int s,
            double a, unsigned int id);
        bool unique_id(unsigned int id);
        bool existant_id(unsigned int id_corail_cible);
        bool seg_superposition();
        bool collision();

        
    private:
        enum TYPE_lecture {ALGUE, CORAIL, SCAVENGER};
        int type;
        unsigned int nbr_algue;
        unsigned int nbr_corail;
        unsigned int nbr_scavenger;

        std::vector<Algue> algue_vect;
        std::vector<Corail> corail_vect; 
        std::vector<Scavenger> scavenger_vect;
};

#endif
