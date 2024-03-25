#ifndef SHAPE_H
#define SHAPE_H

struct S2d {double x=0.; double y=0.;};
bool do_intersect(bool simulation, S2d p1, S2d q1, S2d p2, S2d q2);

class Segments{
    public:
        Segments(double x, double y, double a, unsigned int s);
        double get_angle();
        double get_longueur();
        S2d get_extr();

        bool superposition(Segments s);
        double ecart_angulaire(Segments s);
        

    private:
        S2d base;
        double angle;
        unsigned int longueur;
};

#endif
