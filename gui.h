#ifndef GUI_H
#define GUI_H

#include <gtkmm.h>
#include <gtkmm/window.h>
#include <gtkmm/box.h>
#include <gtkmm/button.h>
#include <gtkmm/drawingarea.h>
#include "simulation.h"


class MyArea : public Gtk::DrawingArea{
public:
    MyArea();
    virtual ~MyArea();

    void exit();
    void open();
    void save();
    void start();
    void step();

protected:
    void on_draw(const Cairo::RefPtr<Cairo::Context>& cr, int width, 
        int height);

private:
    bool empty;
};

class Gui : public Gtk::Window{

public:
    // Constructeur de Gui
    Gui(char * nom_fichier);

protected:
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
    
    Gtk::Box m_Main_Box;
    Gtk::Box m_Buttons_Box;
    
    Gtk::Button m_Button_Exit;
    Gtk::Button m_Button_Open;
    Gtk::Button m_Button_Save;
    Gtk::Button m_Button_Start;
    Gtk::Button m_Button_Step;
};

#endif 
