#include <iostream>
#include "simulation.h"
#include "gui.h"
using namespace std;

int main(int argc, char * argv[]){

    if(argc != 2){
        exit(EXIT_FAILURE);
    };

    Simulation s1;
    s1.lecture(argv[1]);

    auto app = Gtk::Application::create();

	return app->make_window_and_run<Gui>(argc, argv);
}