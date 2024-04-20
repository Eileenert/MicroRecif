#include "gui.h"
#include <cairomm/context.h>
#include <gtkmm/label.h>
#include "graphic.h"
#include <iostream>
#include <string>

using namespace std;

constexpr unsigned int taille_dessin(500); // taille de notre récipient

MyArea::MyArea(): empty(false)
{
	set_content_width(taille_dessin);
	set_content_height(taille_dessin);
	
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

Gui::Gui(char * nom_fichier): 
	
	open_or_save("open"),
    m_Main_Box(Gtk::Orientation::VERTICAL, 0),
	m_Buttons_Box(Gtk::Orientation::VERTICAL, 5),
	
    // Création des boutons
    m_Button_Exit("Exit"),
    m_Button_Open("Open"),  
    m_Button_Save("Save"),
    m_Button_Start("Start"),
    m_Button_Step("Step")
{
	bool simulation_ok = true;
    Simulation s ;
    simulation_ok = s.lecture(nom_fichier);
	if (!simulation_ok){
		s.reintialise_simulation();
	}


    //titre, taille et permission de modifier la taille d ela fenêtre
    set_title("MicroRecif");
    //set_default_size(400,400); on a choisi déjà une taille pour myarea plus haut
	set_resizable(true);
    set_child(m_Main_Box);

    m_Main_Box.append(m_Area);
    m_Main_Box.append(m_Buttons_Box);

    m_Buttons_Box.append(m_Button_Exit);
    m_Buttons_Box.append(m_Button_Open);
    m_Buttons_Box.append(m_Button_Save);
    m_Buttons_Box.append(m_Button_Start);
    m_Buttons_Box.append(m_Button_Step);

    m_Button_Exit.signal_clicked().connect(
		sigc::mem_fun(*this, &Gui::on_button_clicked_exit));
		
    m_Button_Open.signal_clicked().connect(
		sigc::mem_fun(*this, &Gui::on_button_clicked_open));
    
    m_Button_Save.signal_clicked().connect(
		sigc::mem_fun(*this, &Gui::on_button_clicked_save));
		
    m_Button_Start.signal_clicked().connect(
		sigc::mem_fun(*this, &Gui::on_button_clicked_start));

    m_Button_Step.signal_clicked().connect(
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
	cout << "Exit" << endl;
	m_Area.exit();
}

void Gui::on_button_clicked_open(){
	cout << "Open" << endl;
	open_or_save = "open";

	auto dialog = new Gtk::FileChooserDialog("Please choose a file",
		  Gtk::FileChooser::Action::OPEN);
	dialog->set_transient_for(*this);
	dialog->set_modal(true);
	dialog->signal_response().connect(sigc::bind(
	sigc::mem_fun(*this, &Gui::on_file_dialog_response), dialog));
	
	//Add response buttons to the dialog:
	dialog->add_button("_Cancel", Gtk::ResponseType::CANCEL);
	dialog->add_button("_Open", Gtk::ResponseType::OK);
	
	//Add filters, so that only certain file types can be selected:
	
	auto filter_text = Gtk::FileFilter::create();
	filter_text->set_name("Text files");
	filter_text->add_mime_type("text/plain");
	dialog->add_filter(filter_text);
	
	auto filter_cpp = Gtk::FileFilter::create();
	filter_cpp->set_name("C/C++ files");
	filter_cpp->add_mime_type("text/x-c");
	filter_cpp->add_mime_type("text/x-c++");
	filter_cpp->add_mime_type("text/x-c-header");
	dialog->add_filter(filter_cpp);
	
	auto filter_any = Gtk::FileFilter::create();
	filter_any->set_name("Any files");
	filter_any->add_pattern("*");
	dialog->add_filter(filter_any);
	
	//Show the dialog and wait for a user response:
	dialog->show();


	m_Area.open();
}

void Gui::on_button_clicked_save()
{
	cout << "Save" << endl;
	open_or_save = "save";
	auto dialog = new Gtk::FileChooserDialog("Please choose a file",
		  Gtk::FileChooser::Action::SAVE);
	dialog->set_transient_for(*this);
	dialog->set_modal(true);
	dialog->signal_response().connect(sigc::bind(
	sigc::mem_fun(*this, &Gui::on_file_dialog_response), dialog));
	
	//Add response buttons to the dialog:
	dialog->add_button("_Cancel", Gtk::ResponseType::CANCEL);
	dialog->add_button("_Save", Gtk::ResponseType::OK);
	
	//Add filters, so that only certain file types can be selected:
	
	auto filter_text = Gtk::FileFilter::create();
	filter_text->set_name("Text files");
	filter_text->add_mime_type("text/plain");
	dialog->add_filter(filter_text);
	
	auto filter_cpp = Gtk::FileFilter::create();
	filter_cpp->set_name("C/C++ files");
	filter_cpp->add_mime_type("text/x-c");
	filter_cpp->add_mime_type("text/x-c++");
	filter_cpp->add_mime_type("text/x-c-header");
	dialog->add_filter(filter_cpp);
	
	auto filter_any = Gtk::FileFilter::create();
	filter_any->set_name("Any files");
	filter_any->add_pattern("*");
	dialog->add_filter(filter_any);
	
	//Show the dialog
	dialog->show();

	m_Area.save();
}

void Gui::on_button_clicked_start()
{
	cout << "Start" << endl;
	m_Area.start();
}

void Gui::on_button_clicked_step()
{
	cout << "Step" << endl;
	m_Area.step();
}



void Gui::on_file_dialog_response(int response_id, Gtk::FileChooserDialog* dialog)
{
	//Handle the response:
	switch (response_id)
	{
		case Gtk::ResponseType::OK:
		{
		    cout << "Open or Save clicked." << endl;
		
		    //Notice that this is a std::string, not a Glib::ustring.
		    auto filename = dialog->get_file()->get_path();
		    cout << "File selected: " <<  filename << endl;

			if (open_or_save == "open") {
				s.reintialise_simulation();
				s.lecture(const_cast<char*>(filename.c_str()));
				//const_cast<char*>filename.c_str()
			}
			else if (open_or_save == "save"){
				s.sauvegarde(const_cast<char*>(filename.c_str()));
			}
		    break;
		}
		case Gtk::ResponseType::CANCEL:
		{
		    cout << "Cancel clicked." << endl;
		    break;
		}
		default:
		{
		    cout << "Unexpected button clicked." << endl;
		    break;
		}
	}
	delete dialog;
}





