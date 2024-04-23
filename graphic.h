#ifndef GRAPHIC_H
#define GRAPHIC_H
#include <string>
#include <cairomm/context.h>
#include <gtkmm/drawingarea.h>

void cadre();
void  graphic_set_context(const Cairo::RefPtr<Cairo::Context>& cr);
void cercle(double x, double y, std::string type);
void trait(double x1, double y1, double x2, double y2, bool is_alive);
void carre_base_cor(double x, double y, bool is_alive);


#endif