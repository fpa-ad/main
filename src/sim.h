#ifndef __SIM__
#define __SIM__

#include "Particle.h"
#include "plasma.h"
#include <chrono>
#include <string>

using namespace std;

class sim{
    private:
        // name
        string timestamp = "";
        string name = "";
        int snapcount = 0;

        // box dimensions
        double X, Y;
        // grid size
        double dx, dy;
        // time step
        double dt;
        // current time
        double t;

        // plasma
        plasma* sim_plasma = nullptr;

    public:
        // constructor
        sim(double in_X, double in_Y, double in_dx, double in_dy, double in_dt, int n, int* n_particles, int* ctm, auto f);

        // simulation name
        void set_name(string new_name);
        string get_name();

        // snapshot
        void snapshot();

        // run simulation
        void run(double runtime, double sc_dt);

};

#endif