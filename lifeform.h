/* lifeform.h
Orjowane Kaki
Eileen Rheinboldt-Tran
*/
#ifndef LIFEFORM_H
#define LIFEFORM_H

#include <string>
#include <vector>
#include "shape.h"


bool verifie_positive(int nbr);
bool age_positif(int age);
bool longueur_segment(unsigned int s, unsigned int id);
bool verifie_angle(double a, unsigned int id);
bool rayon_scavenger(unsigned int rayon);


class Lifeform
{
public:
    Lifeform(double x1, double y1, unsigned int age1);

    S2d get_coord() const;
    void set_coord(double x_set, double y_set);
    unsigned int get_age() const;
    void older();

protected:
    double x;
    double y;
    unsigned int age;
};


class Algue: public Lifeform
{
public:
    Algue(double x1, double y1, unsigned int age1);
};


class Corail: public Lifeform
{
public:
    Corail(double x1, double y1, int age1, unsigned int id1,
        bool statut_cor1, bool dir_rot1, bool statut_dev1, 
            unsigned int nbr_segments1);

    std::vector<Segments>* get_seg_vector();
    unsigned int get_nbr_segments() const;
    void remove_last_segment();
    unsigned int get_id() const;
    bool get_statut_cor() const;
    bool get_dir_rot() const;
    void set_dir_rot();
    bool get_statut_dev() const;
    void set_statut_dev(bool dev);
    bool get_is_alive() const;
    void add_seg_vector(double a, int s);
    void set_is_alive(bool alive);

private:
    std::vector<Segments> seg_vector;
    unsigned int id;
    bool statut_cor; // 0(DEAD) 1(ALIVE)
    bool dir_rot;   //direction rotation 0(TRIGO) ou 1(INVTRIGO)
    bool statut_dev; // 0(EXTEND) 1(REPRO)
    unsigned int nbr_segments;   
    std::string color; //bleu = alive ou noir = dead
    unsigned int cor_life_max;      
};

class Scavenger: public Lifeform
{
public:
    Scavenger(double x1, double y1,int age1, unsigned int rayon1,
        bool statut_sca1);

    void set_corail_id_cible(unsigned int corail_id_cible1);
    unsigned int get_rayon() const;
    void set_rayon(unsigned int new_rayon);
    bool get_statut_sca() const;
    unsigned int get_corail_id_cible() const;
    void set_statut_sca(bool a); //jsp

private:
    unsigned int rayon;
    bool statut_sca; //0(LIBRE)    1(MANGE)
    unsigned int corail_id_cible;
};

#endif