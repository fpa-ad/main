#ifndef __SIM__
#define __SIM__

#include "particle.h"
#include "plasma.h"

using namespace std;

class sim{
    private:
        // box dimensions
        double X, Y;
        // gridsize
        double dx, dy;
        // time step
        double dt;

        // plasma
        plasma* sim_plasma = nullptr;

    public:
        // construtor
        sim(double in_X, double in_Y, double in_dx, double in_dy, double in_dt, int n, int* n_particles, int* ctm, auto f);



};

#endif