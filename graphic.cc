#define _USE_MATH_DEFINES
#include <cmath>
#include <string>
#include <iostream>
#include "graphic.h"
#include "constantes.h"

using namespace std;

static const Cairo::RefPtr<Cairo::Context>* ptcr(nullptr);

void graphic_set_context(const Cairo::RefPtr<Cairo::Context>& cr){
    ptcr = &cr;
}

void cadre(){
    (*ptcr)->set_line_width(2.);
	(*ptcr)->set_source_rgb(0.5, 0.5, 0.5);

	//dessin du cadre vert
	(*ptcr)->move_to(-250., -250.); 
    (*ptcr)->line_to(250., -250.);
	(*ptcr)->stroke();

	(*ptcr)->move_to(250., -250.); 
    (*ptcr)->line_to(250., 250.);
	(*ptcr)->stroke();

	(*ptcr)->move_to(250., 250.);
    (*ptcr)->line_to(-250., 250.);
	(*ptcr)->stroke();

	(*ptcr)->move_to(-250., 250.);
	(*ptcr)->line_to(-250., -250.);
	(*ptcr)->stroke();
}

//faire un truc avec cr, jsp comment tu veux l'importer
void cercle(double x, double y, string type){
    x -= 250;
    y -= 250;
    if(type == "algue"){  
	    (*ptcr)->set_source_rgb(0.2, 0.8, 0.2);// jsp si c'est le bon rgb
        (*ptcr)->arc(x, y, r_alg, 0, 2*M_PI);
        (*ptcr)->stroke();
    }else if(type == "scavenger"){
        (*ptcr)->set_source_rgb(1, 0, 0); //jsp si c'est le bon rgb
        (*ptcr)->arc(x, y, r_sca, 0, 2*M_PI);
        (*ptcr)->stroke();
    }
}

void trait(double x1, double y1, double x2, double y2, bool is_alive){
    x1 -= 250;
    y1 -= 250;
    x2 -= 250;
    y2 -= 250;

    if(is_alive){
        (*ptcr)->set_source_rgb(0, 0, 1); //jsp si c'est le bon rgb
    }else{
        (*ptcr)->set_source_rgb(0, 0, 0);
    }

    (*ptcr)->move_to(x1, y1); 
    (*ptcr)->line_to(x2, y2);
	(*ptcr)->stroke();

} 

void carre_base_cor(double x, double y, bool is_alive){
    x -= 250;
    y -= 250;

    if(is_alive){
        (*ptcr)->set_source_rgb(0, 0, 1); //jsp si c'est le bon rgb
    }else{
        (*ptcr)->set_source_rgb(0, 0, 0);
    }

    (*ptcr)->move_to(x + d_cor/2., y + d_cor/2.); 
    (*ptcr)->line_to(x + d_cor/2., y - d_cor/ 2.);
	(*ptcr)->stroke();

	(*ptcr)->move_to(x + d_cor/2., y - d_cor/ 2.); 
    (*ptcr)->line_to(x - d_cor/2., y - d_cor/ 2.);
	(*ptcr)->stroke();

	(*ptcr)->move_to(x - d_cor/2., y - d_cor/ 2.);
    (*ptcr)->line_to(x - d_cor/2., y + d_cor/ 2.);
	(*ptcr)->stroke();

	(*ptcr)->move_to(x - d_cor/2., y + d_cor/ 2.);
	(*ptcr)->line_to(x + d_cor/2., y + d_cor/ 2.);
	(*ptcr)->stroke();

}