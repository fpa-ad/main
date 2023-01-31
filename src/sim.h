#ifndef __SIM__
#define __SIM__

#include "particle.h"
#include "plasma.h"
#include <format>
#include <chrono>
#include <string>

using namespace std;

class sim{
    private:
        // name
        string name = format("{0:%F}T{0:%R%z}", chrono::system_clock::now());

        // box dimensions
        double X, Y;
        // grid size
        double dx, dy;
        // time step
        double dt;

        // plasma
        plasma* sim_plasma = nullptr;

    public:
        // constructor
        sim(double in_X, double in_Y, double in_dx, double in_dy, double in_dt, int n, int* n_particles, int* ctm, auto f);

        // simulation name
        void set_name(string new_name);
        string get_name();

};

#endif