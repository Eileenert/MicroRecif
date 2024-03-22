#ifndef LIFEFORM_H
#define LIFEFORM_H
#include <string>
#include <vector>
#include "shape.h"



class Lifeform{
    public:

        Lifeform(double x1, double y1, int age1)
        :x(x1), y(y1), age(age1)
        {}
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

    private:

};


class Corail: public Lifeform{
    public:
        Corail(double x1, double y1,int age1,unsigned int id1, bool statut_cor1, bool dir_rot1, bool statut_dev1, unsigned int nbr_segments1)
        :Lifeform(x1, y1, age1), 
        id(id1), statut_cor(statut_cor1), dir_rot(dir_rot1), statut_dev(statut_dev1), nbr_segments(nbr_segments1)
        {}

        void verifie_angle(size_t index_segment, unsigned id, double a1);
        void verifie_longueur(size_t index_segment, unsigned id, unsigned l);
        void angle_segment(double& angle_seg, double base_x, double base_y,double extr_x, double extr_y);
        std::vector<Segments> get_seg_vector();
        unsigned int get_nbr_segments();
        unsigned int get_id();
        void add_seg_vector(double a, int s);

    private:
        
        //a voir si seg a besoin d'etre ordonne ou non pour appliquer les methodes du cours du 15/03/24
        std::vector<Segments> seg_vector;// si j'ai bien compris un corail a plusieurs segments donc j'ai fait un vecteur

        /*dans le rapport 2.1.2 p.3 je crois qu'il veut des entiers mais je vais demander parce que
        bool est mieux que 0 ou 1 -_('')_- mais il nous donne aussi le nom de certaines variable et 
        peut-être que string c'est bien aussi, jsp a regarder
        */
        unsigned int id;
        bool statut_cor;
        bool dir_rot;   //direction rotation 0(TRIGO) ou 1(INVTRIGO)
        bool statut_dev; // 0(EXTEND) 1(REPRO)
        unsigned int nbr_segments;      //doit être strictement positif --> verifier dans une méthode à l'initialisation
        bool is_alive;
        bool is_extend; // true = EXTEND et false = REPRO
        std::string color; //bleu = alive ou noir = dead pour un prochain rendu, string parce que ensuite on devra surement mettre un code couleur rgb
        unsigned int cor_life_max; 
        
        
};

class Scavenger: public Lifeform{
    public:
        Scavenger(double x1, double y1,int age1, unsigned int rayon1, bool statut_sca1)
        :Lifeform(x1, y1, age1), 
        rayon(rayon1), statut_sca(statut_sca1)
        {}

        void init_corail_id_cible(unsigned int corail_id_cible1);

    private:
        unsigned int rayon;
        bool statut_sca; //0(LIBRE)    1(MANGE)
        unsigned int corail_id_cible;
        
};

#endif