#ifndef GUI_H
#define GUI_H

#include <gtkmm/window.h>
#include <gtkmm/box.h>
#include <gtkmm/button.h>
#include <gtkmm/drawingarea.h>

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
    Gui();

protected:
    void on_button_clicked_exit();
    void on_button_clicked_open();
    void on_button_clicked_save();
    void on_button_clicked_start();
    void on_button_clicked_step();

    MyArea m_Area;
    
    Gtk::Box m_Main_Box;
    Gtk::Box m_Buttons_Box;
    
    Gtk::Button m_Button_exit;
    Gtk::Button m_Button_open;
    Gtk::Button m_Button_save;
    Gtk::Button m_Button_start;
    Gtk::Button m_Button_step;
};

#endif 
