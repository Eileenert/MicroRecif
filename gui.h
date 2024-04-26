/* gui.h
Orjowane Kaki
Eileen Rheinboldt-Tran
*/
#ifndef GUI_H
#define GUI_H

#include <gtkmm.h>
#include <gtkmm/window.h>
#include <gtkmm/box.h>
#include <gtkmm/button.h>
#include <gtkmm/checkbutton.h>
#include <gtkmm/drawingarea.h>
#include "simulation.h"
#include <string>
#include <map> //pour timer



struct Frame // Model Framing and window parameters
{
	double xMin; 
	double xMax;
	double yMin;
	double yMax;
	double asp;  // frame aspect ratio
	int height;  
	int width;  
};

class MyArea : public Gtk::DrawingArea
{
public:
    MyArea(Simulation& sim);
    
    virtual ~MyArea()
    void adjustFrame(int width, int height);

protected:
    void on_draw(const Cairo::RefPtr<Cairo::Context>& cr, int width, 
        int height);

private:
    Frame frame;
    Simulation& s;
};

class Gui : public Gtk::Window
{
public:
    Gui(char * nom_fichier);
    void change_button_name();
    bool step_fonctionne();
    void timer_start_stop(); 
    bool timer_step();
    
protected:
    bool name;
    unsigned int val_maj;
    std::string open_or_save;
    Simulation s ;

    void create_instance(char * nom_fichier);
    void initializeWidgets();
    void connectSignals();

    void update_number();
    void on_button_clicked_exit();
    void on_button_clicked_open();
    void on_button_clicked_save();
    void on_button_clicked_start();
    void on_button_clicked_step();
    void algue_toggled();
    void on_file_dialog_response(int response_id, 
        Gtk::FileChooserDialog* dialog);

    bool on_window_key_pressed(guint keyval, guint keycode, 
        Gdk::ModifierType state);
        
	bool on_timeout();

    MyArea* m_Area;
    
    //VERIFIER CONVENTION POUR LES NOMS
    //prof a fait comme ça dans une serie, doute pour l'incremention

    Gtk::Box m_Main_Box;
    Gtk::Box m_General_Box;
    Gtk::Box m_Buttons_Box;
    Gtk::Box m_Naissance_Algue_Box;
    Gtk::Box m_Info_Box;
    Gtk::Box m_Maj_Box;
    Gtk::Box m_Algue_Box;
    Gtk::Box m_Corail_Box;
    Gtk::Box m_Scavenger_Box;


    Gtk::Label general_Label;

    Gtk::Button m_Button_Exit;
    Gtk::Button m_Button_Open;
    Gtk::Button m_Button_Save;
    Gtk::Button m_Button_Start;
    Gtk::Button m_Button_Step;
    Gtk::CheckButton m_Naissance_Algue_CheckButton;

    Gtk::Label m_Naissance_Algue_Label;

    Gtk::Label info_Label;
    Gtk::Label maj_Label;
    Gtk::Label maj_Data_Label;
    Gtk::Label nbr_Algue_Label;
    Gtk::Label nbr_Algue_Data_Label;
    Gtk::Label nbr_Corail_Label;
    Gtk::Label nbr_Corail_Data_Label;
    Gtk::Label nbr_Scavenger_Label;
    Gtk::Label nbr_Scavenger_Data_Label;

    // to store a single timer disconnect request
	bool disconnect; 
    const int timeout_value; 
};

#endif 
