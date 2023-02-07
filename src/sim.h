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
        string name = "sim";
        int snapcount = 0;

        // box dimensions
        double X, Y;
        // grid size
        double dx, dy;
        // time step
        double dt;
        // current time
        double t = 0;

        // plasma
        plasma sim_plasma;

    public:
        // constructor
        sim(double in_X, double in_Y, double in_dx, double in_dy, double in_dt, int n, int* n_particles, double* ctm, funcdouble** f, int in_nFields, double** const_fields);
        //~sim();

        // simulation name
        void set_name(string new_name);
        string get_name();

        // simulation fullname (timestamp + name)
        string get_fullname();

        // snapshot
        void snapshot();

        // run simulation
        void run(double runtime, double sc_dt);

};

#endif