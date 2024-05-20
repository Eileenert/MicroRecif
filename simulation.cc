/* simulation.cc
Orjowane Kaki 50%
Eileen Rheinboldt-Tran 50%
*/
#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "simulation.h"
#include "message.h"
#include "shape.h"
#include "lifeform.h"

using namespace std;

double distance_deux_points(S2d p1, S2d p2);

Simulation::Simulation(int nbr_al, int nbr_co, int nbr_sca)
    : nbr_algue(nbr_al), nbr_corail(nbr_co), nbr_scavenger(nbr_sca), 
        u(1, maximum-1)
{
}

void Simulation::dessin()
{    
    for(size_t i(0); i < nbr_algue; i++){
        dessin_cercle(algue_vect[i].get_coord(), "algue", r_alg);
    }
    
    for(size_t i(0); i < nbr_corail; i++){
        bool is_alive(corail_vect[i].get_statut_cor()); 
        dessin_carre(corail_vect[i].get_coord(), is_alive);

        for(const Segments& seg : *(corail_vect[i].get_seg_vector())){
            dessin_trait(seg.get_base(), seg.get_extr(), is_alive);
        }
    }

    for(size_t i(0); i< nbr_scavenger; i++){
        dessin_cercle(scavenger_vect[i].get_coord(), "scavenger",
            scavenger_vect[i].get_rayon());
    }
}


void Simulation::sauvegarde(string nom_fichier)
{
    ofstream file(nom_fichier);
    if (file.is_open()){
        file << nbr_algue << endl;
        Algue *a(nullptr);
        Corail *c(nullptr);
        Scavenger *s(nullptr);
        for(size_t i(0); i < nbr_algue ; i++){
            a = &algue_vect[i];
            file << (*a).get_coord().x << " " << (*a).get_coord().y ;
            file << " " << (*a).get_age() << endl;
        }
        file << nbr_corail << endl;
        for(size_t i(0); i < nbr_corail ; i++){
            c = &corail_vect[i];
            file << (*c).get_coord().x << " "<< (*c).get_coord().y << " " ;
            file << (*c).get_age() << " " << (*c).get_id() << " ";
            file << (*c).get_statut_cor() << " " << (*c).get_dir_rot();
            file << " " << (*c).get_statut_dev() << " " ;
            file << (*c).get_nbr_segments() << endl;
            for(size_t j(0); j < (*c).get_nbr_segments() ; j++){
                file << (*c).get_seg_vector()->at(j).get_angle() << " ";
                file << (*c).get_seg_vector()->at(j).get_longueur() << endl;
            }
        }
        file << nbr_scavenger << endl;
        for(size_t i(0); i < nbr_scavenger ; i++){
            s = &scavenger_vect[i];
            file << (*s).get_coord().x << " "<< (*s).get_coord().y << " " ;
            file << (*s).get_age() << " " << (*s).get_rayon() << " ";
            file << (*s).get_statut_sca() << " ";
            file << (*s).get_corail_id_cible() << endl;
        }
        file.close();
    }else{
        cout << "failed to open the file" << endl;
    }
}

void Simulation::execution(bool naissance_algue)
{
    step_algue(naissance_algue);
    step_corail();
    step_scavenger();
}

void Simulation::step_algue(bool naissance_algue)
{
    for(size_t i(0); i < algue_vect.size(); i++){
        algue_vect[i].older();

        if (algue_vect[i].get_age() >= max_life_alg){
            swap(algue_vect[i], algue_vect.back());
            algue_vect.pop_back();
            nbr_algue -=1;
        }
    }

    if(naissance_algue){
        double p(alg_birth_rate);

        bernoulli_distribution b(p); //booléen true avec probabilité p … puis
        bool creer_algue = b(e);
        cout << creer_algue  ;
        if(creer_algue ){
            nbr_algue += 1;
            algue_vect.push_back(Algue(u(e), u(e), 1));
        }
    }

}

void Simulation::step_corail() 
{
    age_and_check_corals();
    
    for (Corail& corail : corail_vect) {
        if (!corail.get_is_alive()){
            continue;
        }
        
        process_coral_growth(corail);
    } 
}


void Simulation::age_and_check_corals()
{
    for(size_t i = 0; i < corail_vect.size(); i++) {
        corail_vect[i].older();

        if (corail_vect[i].get_age() >= max_life_cor) {
            corail_vect[i].set_is_alive(false);
        }
    }
}


void Simulation::process_coral_growth(Corail& corail) 
{
    size_t index_algue = 0;
    if (corail.get_seg_vector()->empty()) {
        cout << "Error: Corail segment vector is empty!" << std::endl;
        return;
    }
    Segments* last_segment = &corail.get_seg_vector()->back();
    double angle_to_use = corail.get_dir_rot() ? -delta_rot : delta_rot;
    
    if (detect_algue(corail, angle_to_use, index_algue, *last_segment)) {
        handle_algue_detection(corail, *last_segment, angle_to_use, 
            index_algue);
    } else {
        update_coral_segment(corail, *last_segment, angle_to_use);
    }
}

void Simulation::handle_algue_detection(Corail& corail, Segments& last_segment, 
    double angle_to_use, size_t index_algue) 
{
    last_segment.set_angle(last_segment.get_angle() + angle_to_use);
    last_segment.set_longueur(last_segment.get_longueur() + delta_l);

    double x = last_segment.get_base().x;
    double y = last_segment.get_base().y;
    unsigned int s = last_segment.get_longueur();
    double a = last_segment.get_angle();
    unsigned int id = corail.get_id();

    if (collision(corail, true) || !extr_appartenance_recipient(x, y, s, a, id) 
        || seg_superposition(corail)) {
        last_segment.set_angle(last_segment.get_angle() - angle_to_use);
        last_segment.set_longueur(last_segment.get_longueur() - delta_l);
        corail.set_dir_rot();
        return;
    } else {
        new_cor(corail, last_segment);
    }

    swap(algue_vect[index_algue], algue_vect.back());
    algue_vect.pop_back();
    nbr_algue -= 1;
}

void Simulation::update_coral_segment(Corail& corail, 
    Segments& last_segment, double angle_to_use) 
{
    last_segment.set_angle(last_segment.get_angle() + angle_to_use);

    double x = last_segment.get_base().x;
    double y = last_segment.get_base().y;
    unsigned int s = last_segment.get_longueur();
    double a = last_segment.get_angle();
    unsigned int id = corail.get_id();

    if (collision(corail, true) || seg_superposition(corail) || 
        !extr_appartenance_recipient(x, y, s, a, id)) {
        corail.set_dir_rot();
    }
}

bool Simulation::detect_algue(Corail corail, double &angle_to_use, size_t &index_algue, Segments last_segment) 
{
    
    bool collision_algue(false);
    double angle(last_segment.get_angle());
    double longueur(last_segment.get_longueur());
    double smaller_angle(delta_rot);
    for (size_t j = 0; j < algue_vect.size(); j++) {
        double d2 = distance_deux_points(last_segment.get_base(), 
            algue_vect[j].get_coord());
        double angle_point = atan2(algue_vect[j].get_coord().y - 
            last_segment.get_base().y, 
                algue_vect[j].get_coord().x - last_segment.get_base().x);
        
        if(d2 <= longueur && abs(angle_point-angle) < smaller_angle){
            bool dans_intervalle(false);
            if (corail.get_dir_rot()) {
                dans_intervalle = (angle_point >= (angle - delta_rot) && 
                    angle_point <= angle);
            } else{
                dans_intervalle = (angle_point <= (angle + delta_rot) && 
                    angle_point >= angle);
            }
            
            if (dans_intervalle) {
                angle_to_use = angle_point - angle;
                smaller_angle = abs(angle_point-angle);
                collision_algue = true;
                index_algue = j;
            }
        }
        
    }
    return collision_algue;
} 

bool Simulation::new_cor(Corail &corail, Segments &last_segment)
{
    if(last_segment.get_longueur() >= l_repro){
        if(corail.get_statut_dev()){
            if(!appartenance_recipient(last_segment.get_extr().x,
             last_segment.get_extr().y) || 
                !extr_appartenance_recipient(last_segment.get_extr().x 
                    , last_segment.get_extr().y, l_repro - l_seg_interne, 
                        last_segment.get_angle(), corail.get_id())){
                last_segment.set_longueur(last_segment.get_longueur() -delta_l);
                return false;
            }
            corail.set_statut_dev(false);
            //trouve un id inexistant
            unsigned int id(0);
            for (Corail corail : corail_vect) {
                if (corail.get_id() == id) {
                    id++;
                }
            }
            double longeur_avant(last_segment.get_longueur());
            corail_vect.push_back(Corail(last_segment.get_extr().x, 
                last_segment.get_extr().y, 
                1, id, 1, 1, 0, 0));
            nbr_corail += 1;
            last_segment.set_longueur(l_repro/2);
            corail_vect.back().add_seg_vector(last_segment.get_angle(), 
                l_repro - l_seg_interne);

            if(collision(corail_vect.back(), true) || 
                seg_superposition(corail_vect.back())){
                corail_vect.pop_back();
                nbr_corail -= 1;
                last_segment.set_longueur(longeur_avant);
                return false;
            }
            
            return true;
        }
        else{
            if(!extr_appartenance_recipient(last_segment.get_extr().x, 
                last_segment.get_extr().y, l_repro - l_seg_interne, 
                    last_segment.get_angle(), corail.get_id())){
                last_segment.set_longueur(last_segment.get_longueur() -delta_l);
                return false;
            }
            corail.set_statut_dev(true);
            corail.add_seg_vector(last_segment.get_angle() ,
                l_repro - l_seg_interne);

            if(collision(corail, true) || seg_superposition(corail)){
                corail.remove_last_segment();
                last_segment.set_longueur(last_segment.get_longueur() -delta_l);
                return false;
            }
        } 
    }  
    return false;
}


double distance_deux_points(S2d p1, S2d p2){
    return sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2));
}
            

void Simulation::step_scavenger()
{
    verifie_old_sca();
    deplacement_vers_corail();
    scavenger_sur_corail();

}

void Simulation::scavenger_sur_corail(){

    //parmis tout les scavengers
    for (size_t i(0); i < scavenger_vect.size(); i++){
        
        //parmi tout les coraux
        for (size_t j(0); j < corail_vect.size(); j++){
            Segments* last_segment = &corail_vect[j].get_seg_vector()->back();
            S2d cor_e = corail_vect[j].get_seg_vector()->back().get_extr();
            S2d seg_b =(*last_segment).get_base();
            S2d sca = scavenger_vect[i].get_coord();
            
            //true or false
            bool sur_corail = ((sca.x == cor_e.x) && (sca.y == cor_e.y));
            bool bon_id = (scavenger_vect[i].get_corail_id_cible() == corail_vect[j].get_id());
            bool mange = (scavenger_vect[i].get_statut_sca() == 1);
            

            //si le scavenger est sur le corail et que le scavenger est en mode mange et que le scavenger a l'id du corail pour cible
            if (sur_corail && mange && bon_id){

                // longeurs du segment du corail
                double L(corail_vect[j].get_seg_vector()->back().get_longueur());
                

                //si la longueur du segment ne vaut pas 0
                if (corail_vect[j].get_seg_vector()->back().get_longueur() != 0){
                    //nouvelles coordonnées pour le scavenger après son déplacement sur le corail
                    double new_x = sca.x + delta_l * (seg_b.x-sca.x)/L;
                    double new_y = sca.y + delta_l * (seg_b.y-sca.y)/L;
                    scavenger_vect[i].set_coord(new_x, new_y);
                    
                    //nouvelle longeur du corail
                    if (corail_vect[j].get_seg_vector()->back().get_longueur() <= delta_l){
                        corail_vect[j].get_seg_vector()->back().set_longueur(0);
                    }else {
                        double new_L = corail_vect[j].get_seg_vector()->back().get_longueur() - delta_l;
                        corail_vect[j].get_seg_vector()->back().set_longueur(new_L);
                    }
                    
                    //nouveau rayon pour le scavenger
                    scavenger_vect[i].set_rayon(scavenger_vect[i].get_rayon() + delta_r_sca);

                    if (corail_vect[j].get_seg_vector()->back().get_longueur() == 0.){
                        cout << corail_vect[j].get_nbr_segments()<< endl;
                        corail_vect[j].remove_last_segment();
                        if(corail_vect[j].get_nbr_segments() == 0){
                            swap(corail_vect[j], corail_vect.back());
                            corail_vect.pop_back();
                            nbr_corail -=1;
                            scavenger_vect[i].set_statut_sca(0);
                        }
                    }
                }
            }

            bool bon_rayon = (scavenger_vect[i].get_rayon() < r_sca_repro);

            if (!bon_rayon){
                //scavenger retreci
                scavenger_vect[i].set_rayon(r_sca);

                //création d'un nouveau scavenger 
                //double d(sqrt(pow(sca.x-seg_b.x, 2) + pow(sca.y-seg_b.y, 2)));
                //double x_repro(sca.x + delta_l * (seg_b.x-sca.x)/d); 
                //double y_repro(sca.y + delta_l * (seg_b.y-sca.y)/d);
                double x_repro(sca.x); 
                double y_repro(sca.y);
                scavenger_vect.push_back(Scavenger(x_repro, y_repro, 1, r_sca, 0));
                nbr_scavenger += 1;
                bon_rayon = true;
            }
        }
    }
}

void Simulation::deplacement_vers_corail(){
    //parmi tout les coraux
    for (size_t j(0); j < corail_vect.size(); j++){
        //je prend les coraux morts
        if (corail_vect[j].get_statut_cor() == 0){ 
            bool already_taken(false);

            //parmi tout les scavengers
            for (size_t i(0); i < scavenger_vect.size(); i++){
                //si le scavenger mange et qu'il a l'id cible du corail j
                if (((scavenger_vect[i].get_statut_sca() == 1) and 
                    (scavenger_vect[i].get_corail_id_cible() == 
                        corail_vect[j].get_id()))){
                    already_taken = true;
                    go_to_dead_cor(i, j);
                }
            } 

            if (already_taken == false){
                dead_libre(); 
                
                for (size_t i(0); i < scavenger_vect.size(); i++){
                //si le scavenger mange et qu'il a l'id cible du corail j
                    if (((scavenger_vect[i].get_statut_sca() == 1) and 
                        (scavenger_vect[i].get_corail_id_cible() == 
                            corail_vect[j].get_id()))){
                        go_to_dead_cor(i, j);
                    }
                }
            }
        }
    }
}

void Simulation::go_to_dead_cor(int i_sca, int i_cor){ 
    double x_sca(scavenger_vect[i_sca].get_coord().x);
    double y_sca(scavenger_vect[i_sca].get_coord().y);
    double x_cor(corail_vect[i_cor].get_seg_vector()->back().get_extr().x);
    double y_cor(corail_vect[i_cor].get_seg_vector()->back().get_extr().y);
    double L(sqrt(pow(x_cor-x_sca, 2) + pow(y_cor-y_sca, 2))); 

    if (L <= delta_l){
        scavenger_vect[i_sca].set_coord(x_cor, y_cor);
        x_sca = scavenger_vect[i_sca].get_coord().x;
        y_sca = scavenger_vect[i_sca].get_coord().y;
        cout << "l : " << x_cor << " et " << x_sca << endl;
    } else {
        double x_tmp = x_sca + (delta_l * (x_cor-x_sca)/L);
        double y_tmp = y_sca + (delta_l * (y_cor-y_sca)/L);
        scavenger_vect[i_sca].set_coord(x_tmp, y_tmp);
    }
}


void Simulation::dead_libre(){
    int i_sca(-1.), j_sca(-1);

    //parmis tout les coraux
    for (size_t j(0); j < corail_vect.size(); j++){  

        //je prend les coraux libres        
        if (corail_vect[j].get_statut_cor() == 0){ 
            bool occupied = false;

            // je regarde si aucun scavenger a déjà le statut de mon corail
            for (size_t i(0); i < scavenger_vect.size(); i++){
                if (scavenger_vect[i].get_corail_id_cible() == corail_vect[j].get_id()){
                    occupied = true;
                    break;
                }
            }

            if (!occupied){
                double Dmin(363.);


                //parmis tout les scavengers
                for (size_t i(0); i < scavenger_vect.size(); i++){
                    

                    //je prend les scavengers libres 
                    if (scavenger_vect[i].get_statut_sca() == 0){
                        
                        S2d cor = corail_vect[j].get_seg_vector()->back().get_extr(); 
                        S2d sca = scavenger_vect[i].get_coord();
            
                        double L(sqrt((pow((cor.x-sca.x), 2)+pow((cor.y-sca.y), 2))));
                        cout << "valeur L  :  " << L <<endl;

                        //on trouve le corail le plus près et on set son id dans la cible du scavenger et on change le statut du scavenger     
                        if (L < Dmin){
                            i_sca = i;
                            j_sca = j;
                            Dmin = L;
                        }
                    }
                }
            }
        }
    }

    if ((i_sca != -1) and (j_sca != -1)){
        scavenger_vect[i_sca].set_corail_id_cible(corail_vect[j_sca].get_id());
        scavenger_vect[i_sca].set_statut_sca(1);
    }
}
               
void Simulation::verifie_old_sca(){
    for(size_t i(0); i < scavenger_vect.size(); i++){
        scavenger_vect[i].older();

        if (scavenger_vect[i].get_age() >= max_life_sca){
            swap(scavenger_vect[i], scavenger_vect.back());
            scavenger_vect.pop_back();
            nbr_scavenger -= 1;
        } //durée de vie scavenger
    }
}

void Simulation::reintialise_simulation()
{
    nbr_algue = 0;
    nbr_corail = 0;
    nbr_scavenger = 0;

    algue_vect.clear();
    corail_vect.clear(); 
    scavenger_vect.clear();
}

bool Simulation::lecture(char * nom_fichier)
{
    string line;
    ifstream fichier(nom_fichier); 

    e.seed(1); // ré-initialiser e à chaque lecture de fichier
    
    type = ALGUE;
    while(getline(fichier >> ws, line))
    {   
        if(line[0]=='#' || line[0]=='\n' || line[0]=='\r') continue; 
        if(!decodage_ligne(line)) return false;
    }

    cout << message::success();

    return true;
}

bool Simulation::decodage_ligne(string line)
{
    bool decodage_ok = true;
    switch(type){
        case ALGUE:
            decodage_ok = decodage_algue(line);
            if (!decodage_ok){
                return false;
            } 
            break;

        case CORAIL:
            decodage_ok = decodage_corail(line);
            if (!decodage_ok) return false;
            break;

        case SCAVENGER:
            decodage_ok = decodage_scavenger(line);
            if (!decodage_ok) return false;
            break;
    } 
    return true;
}

bool Simulation::decodage_algue(string line)
{
    istringstream data(line);
    double x, y;
    int age;

    if(nbr_algue == 0){
        data >> nbr_algue;
        
    }
    else if(algue_vect.size() < nbr_algue){
        data >> x >> y;
        if(!appartenance_recipient(x, y)) {
            return false;}
        data >> age;
        if(!age_positif(age)) return false;
        algue_vect.push_back(Algue(x, y, age));
    }   

    if(algue_vect.size() == nbr_algue){
        type = CORAIL;
        }
    return true;
}

bool Simulation::decodage_corail(string line){
    istringstream data(line);
    double x, y, a;
    int age;
    bool statut, dir_rot, statut_dev;
    unsigned int nbr_segments, id, s;

    //verifie si nbr déjà initialisé
    if(nbr_corail == 0){
        data >> nbr_corail;

        if (nbr_corail == 0){
            type = SCAVENGER;
            return true;
        }
        
    }
    else if((corail_vect.size() != 0) && 
        (corail_vect.back().get_seg_vector()->size() 
            < corail_vect.back().get_nbr_segments())){

        data >> a;
        if(!verifie_angle(a, corail_vect.back().get_id())) return false;
        data >> s;
        if(!longueur_segment(s, corail_vect.back().get_id())) return false;
        if(!extr_appartenance_recipient(x, y, s, a, id)) return false;
        corail_vect.back().add_seg_vector(a,s);   
        if(seg_superposition(corail_vect.back())) return false;
        if(collision(corail_vect.back(), false)) return false;
    }
    else if(corail_vect.size() < nbr_corail){
        data >> x >> y;
        
        if(!appartenance_recipient(x, y)) return false;
        data >> age;
        if(!age_positif(age)) return false;
        data >> id;
        if(!unique_id(id)) return false;
        data >> statut >> dir_rot >> statut_dev >> nbr_segments;
        if(!verifie_positive(nbr_segments)) return false;
        corail_vect.push_back(
            Corail(x, y, age, id, statut, dir_rot, statut_dev, nbr_segments));
        

    }
    if((corail_vect.size()!=0) && (corail_vect.size() == nbr_corail) 
        && (corail_vect.back().get_seg_vector()->size() 
            == corail_vect.back().get_nbr_segments())){
        type = SCAVENGER;
    }
    return true;
}

bool Simulation::decodage_scavenger(string line)
{
    istringstream data(line);
    double x, y;
    unsigned int id_corail_cible;
    unsigned int rayon;
    int age;
    bool statut;
    
    if(nbr_scavenger == 0){
        data >> nbr_scavenger;
    }
    else if(scavenger_vect.size() < nbr_scavenger){
        data >> x >> y;
        if(!appartenance_recipient(x, y)) return false;
        data >> age;
        if(!age_positif(age)) return false;
        data >> rayon;
        if(!rayon_scavenger(rayon)) return false;
        data >> statut;
        scavenger_vect.push_back(Scavenger(x, y, age, rayon, statut));

        if(statut == 1){
            if(data >> id_corail_cible){
                if(!existant_id(id_corail_cible)) return false;
            }
            scavenger_vect.back().set_corail_id_cible(id_corail_cible);
        } 
    }
    return true;
}

bool Simulation::appartenance_recipient(double x, double y)
{
    if((x < 1) || (y < 1) || (x > maximum-1) || (y > maximum-1)){ 
        cout << message::lifeform_center_outside(x, y);
        return false;
    }
    return true;
}


bool Simulation::extr_appartenance_recipient(double x, double y, 
    unsigned int s, double a, unsigned int id)
{
    x = x + s*cos(a);
    y = y + s*sin(a);

    if((x <= epsil_zero) || (x >= maximum - epsil_zero) || (y <= epsil_zero) || 
        (y >= maximum - epsil_zero)){
        cout << message::lifeform_computed_outside(id, x, y); 
        return false;
    }
    return true;
}

bool Simulation::unique_id(unsigned int id)
{
    for(size_t i(0); i < corail_vect.size(); i++){
        if(id == corail_vect[i].get_id()){
            cout << message::lifeform_duplicated_id(id);
            return false;
        }
    }
    return true;
}

bool Simulation::existant_id(unsigned int id_corail_cible)
{
    bool existant_id(false);
    
    for(size_t i(0); i < corail_vect.size(); i++){
        if(id_corail_cible == corail_vect[i].get_id()){
            existant_id = true;
        }
    }
    if(existant_id == false){
        cout << message::lifeform_invalid_id(id_corail_cible);
        return false;
    }
    return true;
}


bool Simulation::seg_superposition(Corail &corail)
{
    bool col(false);
    vector<Segments> seg_vector = *(corail.get_seg_vector());
    unsigned int s1(seg_vector.size()-1);
    unsigned int s2(s1-1);
    
    if(seg_vector.size() >= 2){ 
        Segments s = seg_vector.back();
        col = s.superposition(seg_vector[s2]);
    }
    if(col == 1){
        cout << message::segment_superposition(corail_vect.back().get_id(), 
            s2, s1);
        return true;
    }
    return false;
}


bool Simulation::collision(Corail &corail, bool simulation)
{
    bool col(false);

    //segment qu'on compare
    vector<Segments>* seg1_vector = (corail.get_seg_vector());
    S2d coord1 = (*seg1_vector).back().get_base();
    S2d extr1 = (*seg1_vector).back().get_extr();
  
    for(size_t i(corail_vect.size()-1); i != SIZE_MAX; i--){
        
        vector<Segments> seg2_vector = *(corail_vect[i].get_seg_vector());
        
        for(size_t j(seg2_vector.size()-1); j != SIZE_MAX; j--){
            
            //pas comparer avec lui même et le segment avant
            if(corail_vect[i].get_id() == corail.get_id() && (j == seg2_vector.size()-1)){
                continue;
            }
            //pas comparer avec lui même et le segment d'après
            else if (seg2_vector.size()>=2 && corail_vect[i].get_id() == corail.get_id()  && 
                (j == seg2_vector.size()-2)){
                continue;
            }
            

            S2d coord2 = seg2_vector[j].get_base();
            S2d extr2 = seg2_vector[j].get_extr();


            col = do_intersect(simulation,coord1, extr1, coord2, extr2);
            if(col == true){
                cout << message::segment_collision(corail_vect.back().get_id(), 
                   (*seg1_vector).size()-1 , corail_vect[i].get_id(), j);
                
                return true;
            }
        }
    }
    return false;
}

unsigned int Simulation::get_nbr_algue() const
{
    return nbr_algue;
}
unsigned int Simulation::get_nbr_corail() const
{
    return nbr_corail;
}
unsigned int Simulation::get_nbr_scavenger() const
{
    return nbr_scavenger;
}


