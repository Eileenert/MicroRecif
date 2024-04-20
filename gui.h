#ifndef GUI_H
#define GUI_H

#include <gtkmm/window.h>
#include <gtkmm/box.h>
#include <gtkmm/button.h>
#include <gtkmm/drawingarea.h>
#include <gtkmm.h>

void start_simulation(char * nom_fichier);

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
    bool empty;
};

class Gui : public Gtk::Window{

public:
    // Constructeur de Gui
    Gui();
    void change_button_name();
protected:
    bool name;
    void on_button_clicked_exit();
    void on_button_clicked_open();
    void on_button_clicked_save();
    void on_button_clicked_start();
    void on_button_clicked_step();

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
