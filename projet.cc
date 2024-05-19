/* projet.cc
Orjowane Kaki
Eileen Rheinboldt-Tran
*/

#include <iostream>
#include <gtkmm/application.h>
#include "simulation.h"
#include "gui.h"
using namespace std;

int main(int argc, char * argv[])
{
    auto app = Gtk::Application::create();

    return app->make_window_and_run<Gui>(1, argv, argv[1]);
}