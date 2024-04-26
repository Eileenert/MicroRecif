/* graphic.h
Orjowane Kaki
Eileen Rheinboldt-Tran
*/
#ifndef GRAPHIC_H
#define GRAPHIC_H
#include <string>

void cadre();
void cercle(double x, double y, std::string type, unsigned int rayon);
void trait(double x1, double y1, double x2, double y2, bool is_alive);
void carre_base(double x, double y, bool is_alive);

#endif