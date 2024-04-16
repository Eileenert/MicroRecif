#include "gui.h"
#include <cairomm/context.h>
#include <gtkmm/label.h>
#include "simulation.h"
#include "graphic.h"
#include <iostream>

constexpr int area_side(200); // taille de notre récipient
void reintialise_simulation();
void start_simulation(char * nom_fichier);

MyArea::MyArea(): empty(false)
{
	set_content_width(area_side);
	set_content_height(area_side);
	
	set_draw_func(sigc::mem_fun(*this, &MyArea::on_draw));
}

MyArea::~MyArea()
{
}

void MyArea::exit()
{
	queue_draw();
}

void MyArea::open()
{
	queue_draw();
}

void MyArea::save()
{
	queue_draw();
}

void MyArea::start()
{
	queue_draw();
}

void MyArea::step()
{
	queue_draw();
}

//on dessine dans my area en fonction de la taille de myarea définit plus haut (enfaite myarea c'est notre récipient je crois)
void MyArea::on_draw(const Cairo::RefPtr<Cairo::Context>& cr, int width, int height)
{
	/*if(not empty)
	{
		// coordinates for the center of the window
		int xc, yc;
		xc = width / 2;
		yc = height / 2;

		cr->set_line_width(10.0);

		// draw red lines out from the center of the window
		cr->set_source_rgb(0.8, 0.8, 0.0);
		cr->move_to(0, 0);
		cr->line_to(xc, yc);
		cr->line_to(0, height);
		cr->move_to(xc, yc);
		cr->line_to(width, yc);
		cr->stroke();
	}
	else
	{
		std::cout << "Empty !" << std::endl;
	}*/
}

Gui::Gui(): 
    m_Main_Box(Gtk::Orientation::VERTICAL, 0),
	m_Buttons_Box(Gtk::Orientation::VERTICAL, 5),
	
    // Création des boutons
    m_Button_exit("Exit"),
    m_Button_open("Open"),  
    m_Button_save("Save"),
    m_Button_start("Start"),
    m_Button_step("Step")
{
    //titre, taille et permission de modifier la taille d ela fenêtre
    set_title("MicroRecif");
    //set_default_size(400,400); on a choisi déjà une taille pour myarea plus haut
	set_resizable(true);
    set_child(m_Main_Box);

    m_Main_Box.append(m_Area);
    m_Main_Box.append(m_Buttons_Box);

    m_Buttons_Box.append(m_Button_exit);
    m_Buttons_Box.append(m_Button_open);
    m_Buttons_Box.append(m_Button_save);
    m_Buttons_Box.append(m_Button_start);
    m_Buttons_Box.append(m_Button_step);

    m_Button_exit.signal_clicked().connect(
		sigc::mem_fun(*this, &Gui::on_button_clicked_exit));
		
    m_Button_open.signal_clicked().connect(
		sigc::mem_fun(*this, &Gui::on_button_clicked_open));
    
    m_Button_save.signal_clicked().connect(
		sigc::mem_fun(*this, &Gui::on_button_clicked_save));
		
    m_Button_start.signal_clicked().connect(
		sigc::mem_fun(*this, &Gui::on_button_clicked_start));

    m_Button_step.signal_clicked().connect(
		sigc::mem_fun(*this, &Gui::on_button_clicked_step));
		
}

/*bool Gui::on_window_key_pressed(guint keyval, guint, Gdk::ModifierType state)
{
	switch(gdk_keyval_to_unicode(keyval))
    {
		case 's':
        std::cout << "Action sur la lable bouton start" << std::endl;
        m_Button_start.set_label("start");
        return true;
    }
	return false;
}*/


void Gui::on_button_clicked_exit()
{
	std::cout << "Exit" << std::endl;
	m_Area.exit();
}

void Gui::on_button_clicked_open()
{
	std::cout << "Open" << std::endl;
	m_Area.open();
}

void Gui::on_button_clicked_save()
{
	std::cout << "Save" << std::endl;
	m_Area.save();
}

void Gui::on_button_clicked_start()
{
	std::cout << "Start" << std::endl;
	m_Area.start();
}

void Gui::on_button_clicked_step()
{
	std::cout << "Step" << std::endl;
	m_Area.step();
}


void reintialise_simulation(){
    //ici on devra supprimer tout l'affichage de la simulation
}

void start_simulation(char * nom_fichier){
    bool simulation_ok = true;
    Simulation s ;
    simulation_ok = s.lecture(nom_fichier);
    if(!simulation_ok) reintialise_simulation();
}




