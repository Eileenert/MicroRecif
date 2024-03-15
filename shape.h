struct S2d {double x=0.; double y=0.;};

void bool_superpo();
void bool_intersect_superpo();


class Segments{
    public:
        double get_angle();
        double get_longueur();
        S2d get_extr();

    private:
        S2d base;
        double angle;
        double longueur;
};
