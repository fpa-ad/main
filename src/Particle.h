#ifndef __PARTICLE__
#define __PARTICLE__

using namespace std;

class Particle{
    private:
        // charge to mass ratio
        double ctm;
        // coordinates
        double x, y;
        // velocities
        double vx, vy;

    public:
        // constructor
        Particle(double in_ctm, double in_x, double in_y, double in_vx, double in_vy);
};

#endif