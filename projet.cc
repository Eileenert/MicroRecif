#include <iostream>
#include <gtkmm/application.h>
#include "simulation.h"
#include "gui.h"
using namespace std;

//int main(int argc, char * argv[]){  //ce que tu as fait
int main(int argc, char** argv){
   // if(argc != 2){
    //    exit(EXIT_FAILURE);
   // };

    //start_simulation(argv[1]);

    auto app = Gtk::Application::create();

    // Taille de la fenêtre à l'initialisation // j'ai rajouté pour faire comme Boulic
    //Gtk::Window window;
    //window.set_default_size(200, 200);

    //return app->run(window); //c'est sensé nous permettre de déplacer la fenêtre ou changer sa taille, j'ai rajouté pour faire comme Boulic

    //return app->make_window_and_run<Gui>(1, argv); // ce que tu as fait
    return app->make_window_and_run<Gui>(argc, argv); 
}