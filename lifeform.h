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
        Algue(double x1, double y1, int age1)
        :Lifeform(x1, y1, age1)
        {}

    private:

};


class Corail: public Lifeform{
    public:
        Corail(double x1, double y1, int age1)
        :Lifeform(x1, y1, age1)
        {}

        void verifie_angle(size_t index_segment);
        void verifie_longueur(size_t index_segment);
        void angle_segment(double& angle_seg, double base_x, double base_y,double extr_x, double extr_y);

    private:
        
        //a voir si seg a besoin d'etre ordonne ou non pour appliquer les methodes du cours du 15/03/24
        //jsp pk mais vector ne fonctionne pas donc j'ai mis en commentaire pour l'instant
        //vector<Segments> seg;// si j'ai bien compris un corail a plusieurs segments donc j'ai fait un vecteur

        /*dans le rapport 2.1.2 p.3 je crois qu'il veut des entiers mais je vais demander parce que
        bool est mieux que 0 ou 1 -_('')_- mais il nous donne aussi le nom de certaines variable et 
        peut-être que string c'est bien aussi, jsp a regarder
        */
        bool is_alive;
        bool is_extend; // true = EXTEND et false = REPRO
        bool statut_cor;
        bool statut_dev; // 0(EXTEND) 1(REPRO)
        bool dir_rot;   //direction rotation 0(TRIGO) ou 1(INVTRIGO)
        //jsp pk string ne fonctionne pas donc j'ai mis en commentaire pour l'instant
        //string color; //bleu = alive ou noir = dead pour un prochain rendu, string parce que ensuite on devra surement mettre un code couleur rgb
        unsigned int nbr_segments;      //doit être strictement positif --> verifier dans une méthode à l'initialisation
        unsigned int cor_life_max; 
        double a;
        int s;
        int id;
        
};

class Scavenger: public Lifeform{
    public:
        Scavenger(double x1, double y1, int age1)
        :Lifeform(x1, y1, age1)
        {}

    private:
        bool statut_sca; //0(LIBRE)    1(MANGE)
        int corail_id_cible;

};