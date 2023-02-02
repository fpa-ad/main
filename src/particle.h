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

        double get_ctm();
        double get_x();
        double get_y();
        double get_vx();
        double get_vy();

        // advance function - steps 1 and 2
        void advance_position(double dt, double Ex, double Ey, double Bx, double By);

        // advance function - step 3
        void advance_velocity(double dt, double Ex, double Ey, double Bx, double By);

        // thinking with portals: enabled (aka periodic border conditions)
        void sanity_check(double X, double Y);
};

#endif