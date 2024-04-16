#include "gui.h"
#include "simulation.h"
#include "graphic.h"

Gui::Gui() {

    set_title("MicroRecif");
    set_default_size(200, 200);

}

void reintialise_simulation(){
    //ici on devra supprimer tout l'affichage de la simulation
}


//sera appeler avec un bouton
void start_simulation(char * nom_fichier){
    bool simulation_ok = true;
    Simulation s ;
    simulation_ok = s.lecture(nom_fichier);
    if(!simulation_ok) reintialise_simulation();
}

