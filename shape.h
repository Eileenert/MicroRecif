#ifndef SHAPE_H
#define SHAPE_H

struct S2d {double x=0.; double y=0.;};

void bool_superpo();
void bool_intersect_superpo();


class Segments{
    public:
        Segments(double x, double y, double a, int s);
        double get_angle();
        double get_longueur();
        S2d get_extr();

    private:
        S2d base;
        double angle;
        int longueur;
};

#endif
