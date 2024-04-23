#define _USE_MATH_DEFINES
#include <cmath>
#include "graphic.h"
#include "constantes.h"


//faire un truc avec cr, jsp comment tu veux l'importer
void cercle(double x, double y, string type){

    if(type == "algue"){    
	    cr->set_source_rgb(51, 204, 51);// jsp si c'est le bon rgb
        cr->arc(x, y, r_alg, 0, 2*M_PI);
    }else if(type == "scavenger"){
        cr->set_source_rgb(255, 0, 0); //jsp si c'est le bon rgb
        cr->arc(x, y, r_sca, 0, 2*M_PI);
    }
}

void trait(double x1, double y1, double x2, double y2, bool is_alive){
    if(is_alive){
        cr->set_source_rgb(0, 0, 255); //jsp si c'est le bon rgb
    }else{
        cr->set_source_rgb(0, 0, 0);
    }

    cr->move_to(x1, y1); 
    cr->line_to(x2, y2);
	cr->stroke();

} 

void carre_base_cor(double x, double y, bool is_alive){
    if(is_alive){
        cr->set_source_rgb(0, 0, 255); //jsp si c'est le bon rgb
    }else{
        cr->set_source_rgb(0, 0, 0);
    }

    cr->move_to(x1 + d_cor/2., y1 + d_cor/2.); 
    cr->line_to(x1 + d_cor/2., y1 - d_cor/ 2.);
	cr->stroke();

	cr->move_to(x1 + d_cor/2., y1 - d_cor/ 2.); 
    cr->line_to(x1 - d_cor/2., y1 - d_cor/ 2.);
	cr->stroke();

	cr->move_to(x1 - d_cor/2., y1 - d_cor/ 2.);
    cr->line_to(x1 - d_cor/2., y1 + d_cor/ 2.);
	cr->stroke();

	cr->move_to(x1 - d_cor/2., y1 + d_cor/ 2.);
	cr->line_to(x1 + d_cor/2., y1 + d_cor/ 2.);
	cr->stroke();

}