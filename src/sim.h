#ifndef __SIM__
#define __SIM__

#include "plasma.h"
#include <chrono>
#include <string>
#include "myutils.h"

using namespace std;

class sim{
    private:
        // name
        string timestamp = current_time();
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
        sim(double in_X = 0, double in_Y = 0, double in_dx = 0, double in_dy = 0, double in_dt = 0, int n = 0, int* n_particles = nullptr, double* ctm = nullptr, func** f = nullptr);

        // simulation name
        void set_name(string new_name);
        string get_name();

        // snapshot
        void snapshot();

        // run simulation
        void run(double runtime, double sc_dt);

};

#endif