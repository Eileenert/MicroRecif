/* shape.h
Orjowane Kaki
Eileen Rheinboldt-Tran
*/

#ifndef SHAPE_H
#define SHAPE_H

#include <string>

constexpr double epsil_zero(0.5) ;

struct S2d {double x=0.; double y=0.;};
bool do_intersect(bool simulation, S2d p1, S2d q1, S2d p2, S2d q2);
void dessin_cercle(S2d coord, std::string type, unsigned int rayon);
void dessin_trait(S2d base, S2d extr, bool is_alive);
void dessin_carre(S2d base, bool is_alive);

class Segments
{
public:
    Segments(double x, double y, double a, unsigned int s);
    double get_angle() const;
    void set_angle(double a);
    double get_longueur() const;
    void set_longueur(double l);
    S2d get_extr() const;
    S2d get_base() const;
    void set_base(double x, double y);

    bool superposition(Segments s);
    double ecart_angulaire(Segments s);
private:
    S2d base;
    double angle;
    unsigned int longueur;
};

#endif
