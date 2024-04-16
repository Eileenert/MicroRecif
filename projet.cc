#include <iostream>
#include <gtkmm/application.h>
#include "simulation.h"
#include "gui.h"
using namespace std;

int main(int argc, char * argv[]){
    if(argc != 2){
        exit(EXIT_FAILURE);
    };

    start_simulation(argv[1]);

    auto app = Gtk::Application::create();

    //return app->run(window); //c'est sensé nous permettre de déplacer la fenêtre ou changer sa taille
    return app->make_window_and_run<Gui>(1, argv);
}