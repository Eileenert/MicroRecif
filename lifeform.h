#ifndef LIFEFORM_H
#define LIFEFORM_H
#include <string>
#include <vector>
#include "shape.h"

class Lifeform{
    public:
        Lifeform(double x1, double y1, int age1);

        S2d get_coord() const;

    protected:
        double x;
        double y;
        int age;
};


class Algue: public Lifeform{
    public:
        Algue(double x1, double y1, unsigned int age1)
        :Lifeform(x1, y1, age1)
        {}
};


class Corail: public Lifeform{
    public:
        Corail(double x1, double y1, int age1, unsigned int id1,
            bool statut_cor1, bool dir_rot1, bool statut_dev1, 
                unsigned int nbr_segments1);

        //void angle_segment(double& angle_seg, double base_x,
            // double base_y,double extr_x, double extr_y);
        std::vector<Segments> get_seg_vector() const;
        unsigned int get_nbr_segments() const;
        unsigned int get_id() const;
        void add_seg_vector(double a, int s);

    private:
        std::vector<Segments> seg_vector;

        unsigned int id;
        bool statut_cor;
        bool dir_rot;   //direction rotation 0(TRIGO) ou 1(INVTRIGO)
        bool statut_dev; // 0(EXTEND) 1(REPRO)
        unsigned int nbr_segments;   
        bool is_alive;
        bool is_extend; // true = EXTEND et false = REPRO
        std::string color; //bleu = alive ou noir = dead
        unsigned int cor_life_max;      
};

class Scavenger: public Lifeform{
    public:
        Scavenger(double x1, double y1,int age1, unsigned int rayon1,
            bool statut_sca1);

        void init_corail_id_cible(unsigned int corail_id_cible1);

    private:
        unsigned int rayon;
        bool statut_sca; //0(LIBRE)    1(MANGE)
        unsigned int corail_id_cible;
};

#endif