#ifndef __PARTICLE__
#define __PARTICLE__

using namespace std;

class particle{
    private:
        // charge to mass ratio
        double ctm;
        // coordinates
        double x, y;
        // velocities
        double vx, vy;

    public:
        // constructor
        particle(double in_ctm, double in_x, double in_y, double in_vx, double in_vy);

        // return charge to mass ratio
        double get_ctm();

        // return current x position
        double get_x();

        // return current y position
        double get_y();

        // return current x velocity
        double get_vx();

        // return current y velocity
        double get_vy();

        // advance function - steps 1 and 2
        void advance_position(double dt, double Ex, double Ey, double Ez, double Bx, double By, double Bz);

        // advance function - step 3
        void advance_velocity(double dt, double Ex, double Ey, double Ez, double Bx, double By, double Bz);

        // thinking with portals: enabled (aka periodic border conditions)
        void sanity_check(double X, double Y);
};

#endif