#ifndef GUI_H
#define GUI_H

#include <gtkmm/window.h>
#include <gtkmm/box.h>
#include <gtkmm/button.h>
#include <gtkmm/drawingarea.h>

class Gui : public Gtk::Window{
    public:

    protected:
        Gtk::Button m_Button_start;
        Gtk::Button m_Button_step;

};

#endif