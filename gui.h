#ifndef GUI_H
#define GUI_H

#include <gtkmm.h>
#include <gtkmm/window.h>
#include <gtkmm/box.h>
#include <gtkmm/button.h>
#include <gtkmm/drawingarea.h>
#include "simulation.h"
#include <string>


struct Frame // Model Framing and window parameters
{
	double xMin; // frame parameters
	double xMax;
	double yMin;
	double yMax;
	double asp;  // frame aspect ratio
	int height;  // window height
	int width;   // window width
};

class MyArea : public Gtk::DrawingArea{
public:
    MyArea();
    virtual ~MyArea();

    void setFrame(Frame x); 
    void adjustFrame(int width, int height);

protected:
    void on_draw(const Cairo::RefPtr<Cairo::Context>& cr, int width, 
        int height);

private:
    Frame frame;
};

class Gui : public Gtk::Window{

public:
    // Constructeur de Gui
    Gui(char * nom_fichier);
    void change_button_name();
    

protected:
    bool name;
    std::string open_or_save;
    Simulation s ;

    void on_button_clicked_exit();
    void on_button_clicked_open();
    void on_button_clicked_save();
    void on_button_clicked_start();
    void on_button_clicked_step();

    void on_file_dialog_response(int response_id, Gtk::FileChooserDialog* dialog);

    // pour cliquer depuis le clavier
    bool on_window_key_pressed(guint keyval, guint keycode, 
        Gdk::ModifierType state);

    MyArea m_Area;
    
    //VERIFIER CONVENTION POUR LES NOMS

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
};

#endif 
