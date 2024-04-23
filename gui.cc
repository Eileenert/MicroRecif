#include "gui.h"
#include <cairomm/context.h>
#include <gtkmm/label.h>
#include "graphic.h"
#include <iostream>
//#include <string> y'a déjà un string dans gui.h

using namespace std;

static Frame default_frame = {-250., 250., -250., 250., 1., 500, 500};

constexpr unsigned int taille_dessin(500); // taille de notre récipient

static void draw_frame(const Cairo::RefPtr<Cairo::Context>& cr, Frame frame);
static void orthographic_projection(const Cairo::RefPtr<Cairo::Context>& cr, 
									Frame frame);
//taille du récipient
MyArea::MyArea()
{
	set_content_width(taille_dessin);
	set_content_height(taille_dessin);
	
	set_draw_func(sigc::mem_fun(*this, &MyArea::on_draw));
}

MyArea::~MyArea()
{
}

// defining the Model space frame to visualize in the window canvas
void MyArea::setFrame(Frame f)
{
	if((f.xMin <= f.xMax) and (f.yMin <= f.yMax) and (f.height > 0))
	{
		f.asp = f.width/f.height;
		frame = f;
	}
	else
		std::cout << "incorrect Model framing or window parameters" << std::endl;
}

void MyArea::adjustFrame(int width, int height)
{
	frame.width  = width;
	frame.height = height;

	// Preventing distorsion by adjusting the frame (cadrage)
	// to have the same proportion as the graphical area
	
    // use the reference framing as a guide for preventing distortion
    double new_aspect_ratio((double)width/height);
    if( new_aspect_ratio > default_frame.asp)
    { // keep yMax and yMin. Adjust xMax and xMin
	    frame.yMax = default_frame.yMax ;
	    frame.yMin = default_frame.yMin ;	
	  
	    double delta(default_frame.xMax - default_frame.xMin);
	    double mid((default_frame.xMax + default_frame.xMin)/2);
        // the new frame is centered on the mid-point along X
	    frame.xMax = mid + 0.5*(new_aspect_ratio/default_frame.asp)*delta ;
	    frame.xMin = mid - 0.5*(new_aspect_ratio/default_frame.asp)*delta ;		  	  
    }
    else
    { // keep xMax and xMin. Adjust yMax and yMin
	    frame.xMax = default_frame.xMax ;
	    frame.xMin = default_frame.xMin ;
	  	  
 	    double delta(default_frame.yMax - default_frame.yMin);
	    double mid((default_frame.yMax + default_frame.yMin)/2);
        // the new frame is centered on the mid-point along Y
	    frame.yMax = mid + 0.5*(default_frame.asp/new_aspect_ratio)*delta ;
	    frame.yMin = mid - 0.5*(default_frame.asp/new_aspect_ratio)*delta ;		  	  
    }
}

//on dessine dans my area en fonction de la taille de myarea définit plus haut (enfaite myarea c'est notre récipient je crois)
void MyArea::on_draw(const Cairo::RefPtr<Cairo::Context>& cr, int width, int height)
{
	adjustFrame(width, height);
	draw_frame(cr, frame);  // drawing the drawingArea space
	
	orthographic_projection(cr, frame); // set the transformation MODELE to GTKmm

	cr->set_line_width(2.);
	cr->set_source_rgb(0.5, 0.5, 0.5);

	//dessin du cadre vert
	cr->move_to(-250., -250.); 
    cr->line_to(250., -250.);
	cr->stroke();

	cr->move_to(250., -250.); 
    cr->line_to(250., 250.);
	cr->stroke();

	cr->move_to(250., 250.);
    cr->line_to(-250., 250.);
	cr->stroke();

	cr->move_to(-250., 250.);
	cr->line_to(-250., -250.);
	cr->stroke();
}



//enfaite le numéro 5 que j'ai rajouté, c'est juste pour mettre d el'espace entre les boutons, tu peux essayer de changer si tu veux
Gui::Gui(char * nom_fichier):
	name(true),
	open_or_save("open"),
    m_Main_Box(Gtk::Orientation::HORIZONTAL, 5),
	m_General_Box(Gtk::Orientation::VERTICAL, 20),
	m_Buttons_Box(Gtk::Orientation::VERTICAL, 5),
	m_Naissance_Algue_Box(Gtk::Orientation::HORIZONTAL, 5),
	m_Info_Box(Gtk::Orientation::VERTICAL, 10),
	m_Maj_Box(Gtk::Orientation::HORIZONTAL, 50),
    m_Algue_Box(Gtk::Orientation::HORIZONTAL, 80),
    m_Corail_Box(Gtk::Orientation::HORIZONTAL, 78),
    m_Scavenger_Box(Gtk::Orientation::HORIZONTAL, 43),

	general_Label("General"),

    // Création des boutons
    m_Button_Exit("Exit"),
    m_Button_Open("Open"),  
    m_Button_Save("Save"),
    m_Button_Start("Start"),
    m_Button_Step("Step"),
	m_Naissance_Algue_Label("Naissance d'algue"),
	info_Label("info: nombre de ..."),
    maj_Label("mise à jour:"),
    maj_Data_Label("0"),
    nbr_Algue_Label("algues:"),
    nbr_Algue_Data_Label(to_string(s.get_nbr_algue())),
    nbr_Corail_Label("corails:"),
    nbr_Corail_Data_Label(to_string(s.get_nbr_corail())),
    nbr_Scavenger_Label("charognards"),
    nbr_Scavenger_Data_Label(to_string(s.get_nbr_scavenger())),
    timer_added(false),
    disconnect(false),
    timeout_value(500)

{
	bool simulation_ok = true;
    simulation_ok = s.lecture(nom_fichier);
	
	if (!simulation_ok){
		s.reintialise_simulation();
	}
	s.dessin();

	m_Area.set_expand();

    //titre, taille et permission de modifier la taille d ela fenêtre
    set_title("MicroRecif");
    set_default_size(700, 700); //taille du Main_Box
	set_resizable(true);
    set_child(m_Main_Box);

	m_General_Box.set_margin(5);
	m_General_Box.append(m_Buttons_Box);
	m_General_Box.append(m_Info_Box);

	m_Main_Box.append(m_General_Box);
    m_Main_Box.append(m_Area);
	
	m_Info_Box.append(info_Label);
	m_Info_Box.append(m_Maj_Box);
	m_Info_Box.append(m_Algue_Box);
	m_Info_Box.append(m_Corail_Box);
	m_Info_Box.append(m_Scavenger_Box);

	m_Buttons_Box.append(general_Label);
    m_Buttons_Box.append(m_Button_Exit);
    m_Buttons_Box.append(m_Button_Open);
    m_Buttons_Box.append(m_Button_Save);
    m_Buttons_Box.append(m_Button_Start);
    m_Buttons_Box.append(m_Button_Step);
	m_Buttons_Box.append(m_Naissance_Algue_Box);
	m_Naissance_Algue_Box.append(m_Naissance_Algue_CheckButton);
	m_Naissance_Algue_Box.append(m_Naissance_Algue_Label);

	m_Maj_Box.append(maj_Label);
	m_Maj_Box.append(maj_Data_Label);
	m_Algue_Box.append(nbr_Algue_Label);
	m_Algue_Box.append(nbr_Algue_Data_Label);
	m_Corail_Box.append(nbr_Corail_Label);
	m_Corail_Box.append(nbr_Corail_Data_Label);
	m_Scavenger_Box.append(nbr_Scavenger_Label);
	m_Scavenger_Box.append(nbr_Scavenger_Data_Label);

    m_Button_Exit.signal_clicked().connect(
		sigc::mem_fun(*this, &Gui::on_button_clicked_exit));//pour timer
		
    m_Button_Open.signal_clicked().connect(
		sigc::mem_fun(*this, &Gui::on_button_clicked_open));
    
    m_Button_Save.signal_clicked().connect(
		sigc::mem_fun(*this, &Gui::on_button_clicked_save));
		
    m_Button_Start.signal_clicked().connect(
		sigc::mem_fun(*this, &Gui::on_button_clicked_start)); //pour timer

    m_Button_Step.signal_clicked().connect(
		sigc::mem_fun(*this, &Gui::on_button_clicked_step));


	auto controller = Gtk::EventControllerKey::create();
    controller->signal_key_pressed().connect(
                  sigc::mem_fun(*this, &Gui::on_window_key_pressed), false);
    add_controller(controller);
	
}

bool Gui::on_window_key_pressed(guint keyval, guint, Gdk::ModifierType state)
{
	switch(gdk_keyval_to_unicode(keyval))
    {
	case 's' :
		change_button_name();
		timer_start_stop();
		return true;
	case '1' :
		step_fonctionne();
    }
	return false;
}

static void draw_frame(const Cairo::RefPtr<Cairo::Context>& cr, Frame frame)
{
	//display a rectangular frame around the drawing area
	cr->set_line_width(2.0);
	// draw gray lines
	cr->set_source_rgb(0.5, 0.5, 0.5);
	cr->rectangle(0,0, frame.width, frame.height);
	cr->stroke();
}

static void orthographic_projection(const Cairo::RefPtr<Cairo::Context>& cr, 
								    Frame frame)
{
	// déplace l'origine au centre de la fenêtre
	cr->translate(frame.width/2, frame.height/2);
  
	// normalise la largeur et hauteur aux valeurs fournies par le cadrage
	// ET inverse la direction de l'axe Y
	cr->scale(frame.width/(frame.xMax - frame.xMin), 
             -frame.height/(frame.yMax - frame.yMin));
  
	// décalage au centre du cadrage
	cr->translate(-(frame.xMin + frame.xMax)/2, -(frame.yMin + frame.yMax)/2);
}


void Gui::on_button_clicked_exit()
{
	hide();//mieux que exit(0); à mon avis
}

void Gui::on_button_clicked_open()
{
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
}


void Gui::on_button_clicked_start()//equivalent de on_button_add_timer
{
	change_button_name();
	timer_start_stop();
}

void Gui::on_button_clicked_step()
{
	step_fonctionne();
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

void Gui::change_button_name(){
	if(name) {
			cout << "clavier, start" <<endl;
        	m_Button_Start.set_label("Stop");
			m_Button_Step.set_sensitive(false);
		}
		else{
			cout << "calvier stop" <<endl;
			m_Button_Start.set_label("Start");
			m_Button_Step.set_sensitive(true);
		}
		name = !name;
}

bool Gui::step_fonctionne(){
	if(name) {
		cout << "clavier, step" << endl;
        m_Button_Step.set_label("Step");
    return true;
	} else { return false; }
}

//=============POUR TIMER

bool Gui::on_timeout()
{
	static unsigned int val(1);
	
	if(disconnect)
	{
		disconnect = false; // reset for next time a Timer is created
		
		return false; // End of Timer 
	}
	
	maj_Data_Label.set_text(std::to_string(val));  // display he simulation clock
	
	cout << "This is simulation update number : " << val << endl;

	++val;
	return true; 
}

void Gui::timer_start_stop(){
	if(!name)
	{
		if(not timer_added)
		{	  
			// Creation of a new object prevents long lines and shows us a little
			// how slots work.  We have 0 parameters and bool as a return value
			// after calling sigc::bind.
			sigc::slot<bool()> my_slot = sigc::bind(sigc::mem_fun(*this,
		                                        	&Gui::on_timeout));
		
			// This is where we connect the slot to the Glib::signal_timeout()
			auto conn = Glib::signal_timeout().connect(my_slot,timeout_value);
			
			timer_added = true;
		
			cout << "Timer added" << endl;
		}
		else
		{
	   		cout << "The timer already exists: nothing more is created" << endl;
		}
	}
	else
	{
		if(not timer_added)
		{
			cout << "Sorry, there is no active timer at the moment." << endl;
		}
		else
		{
			cout << "manually disconnecting the timer " << endl;
			disconnect  = true;   
			timer_added = false;
		}
	}
}



