#include "shape.h"

class Lifeform{

    private:
        int nbr_entite;
};


class Corail: public Lifeform{
    public:

    void verifie_angle(size_t index_segment);
    void verifie_longueur(size_t index_segment);
    void angle_segment(double& angle_seg, double base_x, double base_y,double extr_x, double extr_y);

    private:
        
        //a voir si seg a besoin d'etre ordonne ou non pour appliquer les methodes du cours du 15/03/24
        vector<Segments> seg;// si j'ai bien compris un corail a plusieurs segments donc j'ai fait un vecteur

        /*dans le rapport 2.1.2 p.3 je crois qu'il veut des entiers mais je vais demander parce que
        bool est mieux que 0 ou 1 -_('')_- mais il nous donne aussi le nom de certaines variable et 
        peut-être que string c'est bien aussi, jsp a regarder
        */
        bool is_alive;
        bool is_extend; // true = EXTEND et false = REPRO
        string dir_rot;   //direction rotation (TRIGO) ou (INVTRIGO)
        string color; //bleu = alive ou noir = dead pour un prochain rendu, string parce que ensuite on devra surement mettre un code couleur rgb
        unsigned int nbr_segments;      //doit être strictement positif --> verifier dans une méthode à l'initialisation
        unsigned int cor_life_max; 
        
};

class Scavenger: public Lifeform{

};

class Algue: public Lifeform{

};