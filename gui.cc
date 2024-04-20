#include "gui.h"
#include <cairomm/context.h>
#include <gtkmm/label.h>
#include "simulation.h"
#include "graphic.h"
#include <iostream>

using namespace std;

static Frame default_frame = {-150., 150., -100., 100., 1.5, 300, 200};

constexpr unsigned int taille_dessin(500); // taille de notre récipient

static void draw_frame(const Cairo::RefPtr<Cairo::Context>& cr, Frame frame);
static void orthographic_projection(const Cairo::RefPtr<Cairo::Context>& cr, 
									Frame frame);


MyArea::MyArea(): empty(false)
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
	if(not empty)   // drawing in the Model space
	{
		// adjust the frame (cadrage) to prevent distortion 
		adjustFrame(width, height);
		draw_frame(cr, frame);              // drawing the drawingArea space
	
		orthographic_projection(cr, frame); // set the transformation MODELE to GTKmm
	}
	else
	{
		cout << "Empty !" << endl;
	}
}

Gui::Gui(): 
	name(true),
    m_Main_Box(Gtk::Orientation::VERTICAL, 0),
	m_Buttons_Box(Gtk::Orientation::VERTICAL, 5),
	
    // Création des boutons
    m_Button_Exit("Exit"),
    m_Button_Open("Open"),  
    m_Button_Save("Save"),
    m_Button_Start("Start"),
    m_Button_Step("Step")
{
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
		return true;
	case '1' :
		cout << "clavier, step" <<endl;
        m_Button_Step.set_label("Step");
        return true;
    }
	return false;
}

static void draw_frame(const Cairo::RefPtr<Cairo::Context>& cr, Frame frame)
{
	//display a rectangular frame around the drawing area
	cr->set_line_width(5.0);
	// draw greenish lines
	cr->set_source_rgb(0., 0., 0.);
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
	cout << "Exit" << endl;
	exit(0);
}

void Gui::on_button_clicked_open()
{
	cout << "Open" << endl;
}

void Gui::on_button_clicked_save()
{
	cout << "Save" << endl;
}


void Gui::on_button_clicked_start()
{
	change_button_name();
}

void Gui::on_button_clicked_step()
{
	cout << "Step" << endl;
}


void start_simulation(char * nom_fichier){
    bool simulation_ok = true;
    Simulation s ;
    simulation_ok = s.lecture(nom_fichier);
	if (!simulation_ok){
		s.reintialise_simulation();
	}
	s.sauvegarde("save.txt");
}

void Gui::change_button_name(){
	if(name) {
			cout << "clavier, start" <<endl;
        	m_Button_Start.set_label("Stop");
		}
		else{
			cout << "calvier stop" <<endl;
			m_Button_Start.set_label("Start");
		}
		name = !name;
}



