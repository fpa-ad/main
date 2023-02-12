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
        //@param in_ctm charge to mass ratio
        //@param in_x starting x position
        //@param in_y starting y position
        //@param in_vx starting x velocity
        //@param in_vy starting y velocity
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

        // advance function - Verlet steps 1 and 2
        //@param dt time step
        //@param Ex electric field at the particle's position, x direction
        //@param Ey electric field at the particle's position, y direction
        //@param Ez electric field at the particle's position, z direction
        //@param Bx magnetic field at the particle's position, x direction
        //@param By magnetic field at the particle's position, y direction
        //@param Bz magnetic field at the particle's position, z direction
        void advance_position(double dt, double Ex, double Ey, double Ez, double Bx, double By, double Bz);

        // advance function - Verlet step 3
        //@param Ex electric field at the particle's position, x direction
        //@param Ey electric field at the particle's position, y direction
        //@param Ez electric field at the particle's position, z direction
        //@param Bx magnetic field at the particle's position, x direction
        //@param By magnetic field at the particle's position, y direction
        //@param Bz magnetic field at the particle's position, z direction
        void advance_velocity(double dt, double Ex, double Ey, double Ez, double Bx, double By, double Bz);

        // thinking with portals: enabled (aka periodic border conditions)
        //@param X x length of the box
        //@param Y y length of the box
        void sanity_check(double X, double Y);
};

#endif