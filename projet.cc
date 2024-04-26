#include <iostream>
#include <gtkmm/application.h>
#include "simulation.h"
#include "gui.h"
using namespace std;

//int main(int argc, char * argv[]){  //ce que tu as fait
int main(int argc, char * argv[])
{
    //FAIRE QUE SI PAS DE DEUXIEME ARGUEMENT NE PAS ARREZER ET METTRE ""
    if(argc != 2){
        exit(EXIT_FAILURE);
    };

    auto app = Gtk::Application::create();

    //return app->run(window); //c'est sensé nous permettre de déplacer la fenêtre ou changer sa taille
    return app->make_window_and_run<Gui>(1, argv, argv[1]);

}