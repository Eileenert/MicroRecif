/* graphic.cc
Orjowane Kaki 50%
Eileen Rheinboldt-Tran 50%
*/
#define _USE_MATH_DEFINES
#include <cmath>
#include <string>
#include <iostream>
#include "graphic.h"
#include "graphic_gui.h"

using namespace std;

static const Cairo::RefPtr<Cairo::Context> *ptcr(nullptr);

void graphic_set_context(const Cairo::RefPtr<Cairo::Context> &cr)
{
    ptcr = &cr;
}

void cadre()
{
    (*ptcr)->set_line_width(1.);
    (*ptcr)->set_source_rgb(0.5, 0.5, 0.5);

    (*ptcr)->move_to(0., 0.);
    (*ptcr)->line_to(256., 0.);
    (*ptcr)->stroke();

    (*ptcr)->move_to(256., 0.);
    (*ptcr)->line_to(256., 256.);
    (*ptcr)->stroke();

    (*ptcr)->move_to(256., 256.);
    (*ptcr)->line_to(0., 256.);
    (*ptcr)->stroke();

    (*ptcr)->move_to(0., 256.);
    (*ptcr)->line_to(0., 0.);
    (*ptcr)->stroke();
}

// faire un truc avec cr, jsp comment tu veux l'importer
void cercle(double x, double y, string type, unsigned int rayon)
{
    (*ptcr)->set_line_width(1.);
    if (type == "algue"){
        (*ptcr)->set_source_rgb(0, 1, 0);
    }
    else if (type == "scavenger"){
        (*ptcr)->set_source_rgb(1, 0, 0);
    }
    (*ptcr)->arc(x, y, rayon, 0, 2 * M_PI);
    (*ptcr)->stroke();
}

void trait(double x1, double y1, double x2, double y2, bool is_alive)
{
    (*ptcr)->set_line_width(1.);
    if (is_alive){
        (*ptcr)->set_source_rgb(0, 0, 1);
    }
    else{
        (*ptcr)->set_source_rgb(0, 0, 0);
    }

    (*ptcr)->move_to(x1, y1);
    (*ptcr)->line_to(x2, y2);
    (*ptcr)->stroke();
}

void carre_base(double x, double y, bool is_alive)
{
    constexpr unsigned d_cor(3);

    (*ptcr)->set_line_width(1.);
    if (is_alive){
        (*ptcr)->set_source_rgb(0, 0, 1);
    }
    else{
        (*ptcr)->set_source_rgb(0, 0, 0);
    }

    (*ptcr)->move_to(x + d_cor / 2., y + d_cor / 2.);
    (*ptcr)->line_to(x + d_cor / 2., y - d_cor / 2.);
    (*ptcr)->stroke();

    (*ptcr)->move_to(x + d_cor / 2., y - d_cor / 2.);
    (*ptcr)->line_to(x - d_cor / 2., y - d_cor / 2.);
    (*ptcr)->stroke();

    (*ptcr)->move_to(x - d_cor / 2., y - d_cor / 2.);
    (*ptcr)->line_to(x - d_cor / 2., y + d_cor / 2.);
    (*ptcr)->stroke();

    (*ptcr)->move_to(x - d_cor / 2., y + d_cor / 2.);
    (*ptcr)->line_to(x + d_cor / 2., y + d_cor / 2.);
    (*ptcr)->stroke();
}