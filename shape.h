#ifndef SHAPE_H
#define SHAPE_H

constexpr double epsil_zero(0.5) ;

struct S2d {double x=0.; double y=0.;};
bool do_intersect(bool simulation, S2d p1, S2d q1, S2d p2, S2d q2);
void dessin_algues(S2d coord);
void dessin_trait(S2d base, S2d extr, bool is_alive);
void dessin_base_cor(S2d base, bool is_alive);
void dessin_sca(S2d coord);

class Segments{
    public:
        Segments(double x, double y, double a, unsigned int s);
        double get_angle() const;
        double get_longueur() const;
        S2d get_extr() const;
        S2d get_base() const;

        bool superposition(Segments s);
        double ecart_angulaire(Segments s);
    private:
        S2d base;
        double angle;
        unsigned int longueur;
};

#endif
