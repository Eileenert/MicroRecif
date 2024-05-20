/* simulation.h
Orjowane Kaki
Eileen Rheinboldt-Tran
*/
#ifndef SIMULATION_H
#define SIMULATION_H
#include "lifeform.h"
#include "constantes.h"
#include <vector>
#include <string>
#include <random>


class Simulation
{
public:
    Simulation(int nbr_al = 0, int nbr_co = 0, int nbr_sca = 0);

    void sauvegarde(std::string nom_fichier);
    void execution(bool naissance_algue);
    void step_algue(bool naissance_algue);
    void step_corail();
    void step_scavenger();
    void verifie_old_sca();
    void deplacement_vers_corail();
    void scavenger_sur_corail();
    void dead_libre();
    void go_to_dead_cor(int i_sca, int i_cor);
    void reintialise_simulation();
    void dessin();

    void age_and_check_corals();
    void process_coral_growth(Corail& corail);
    void handle_algue_detection(Corail& corail, Segments& last_segment, double angle_to_use, size_t index_algue);
    void update_coral_segment(Corail& corail, Segments& last_segment, double angle_to_use);
    bool detect_algue(Corail corail, double &angle_to_use, size_t &index_algue, Segments last_segment);
    bool new_cor(Corail &corail, Segments &last_segment);
    bool angle_collision(Corail &corail, Segments &last_segment, double &angle_to_use);

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
    bool seg_superposition(Corail &corail);
    bool collision(Corail &corail, bool simulation);

    unsigned int get_nbr_algue() const;
    unsigned int get_nbr_corail() const;
    unsigned int get_nbr_scavenger() const;
    
private:
    enum TYPE_lecture {ALGUE, CORAIL, SCAVENGER};
    int type;
    unsigned int nbr_algue;
    unsigned int nbr_corail;
    unsigned int nbr_scavenger;

    std::vector<Algue> algue_vect;
    std::vector<Corail> corail_vect; 
    std::vector<Scavenger> scavenger_vect;

    std::default_random_engine e;
    std::uniform_int_distribution<unsigned> u;
};

#endif
