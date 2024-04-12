#ifndef GUI_H
#define GUI_H

#include <gtkmm/window.h>
#include <gtkmm/box.h>
#include <gtkmm/button.h>
#include <gtkmm/drawingarea.h>

class Gui : public Gtk::Window{
    public:
        // Constructeur de Gui
        Gui() {
        // Création des boutons
        m_Button_exit.set_label("Exit");
        m_Button_open.set_label("Open");   
        m_Button_save.set_label("Save"); 
        m_Button_start.set_label("Start");
        m_Button_step.set_label("Step");  

        // Ajout des boutons à la boîte verticale
        m_Box.pack_start(m_Button_exit, Gtk::PACK_EXPAND_WIDGET);
        m_Box.pack_start(m_Button_open, Gtk::PACK_EXPAND_WIDGET);
        m_Box.pack_start(m_Button_save, Gtk::PACK_EXPAND_WIDGET); 
        m_Box.pack_start(m_Button_start, Gtk::PACK_EXPAND_WIDGET);
        m_Box.pack_start(m_Button_step, Gtk::PACK_EXPAND_WIDGET); 

        // Ajout de la boîte à la fenêtre
        add(m_Box);

        // Affichage des éléments
        show_all();
        }

    protected:
        Gtk::Button m_Button_exit;
        Gtk::Button m_Button_open;
        Gtk::Button m_Button_save;
        Gtk::Button m_Button_start;
        Gtk::Button m_Button_step;
        Gtk::Box m_Box{Gtk::ORIENTATION_VERTICAL}; 

};

#endif 
