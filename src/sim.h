#ifndef __SIM__
#define __SIM__

#include "plasma.h"
#include <chrono>
#include <string>
#include "myutils.h"

using namespace std;

class sim{
    private:
        // timestamp
        string timestamp = current_time();
        // name
        string name = "sim";

        // box dimensions
        double X, Y;
        // grid size
        double dx, dy;
        // time step
        double dt;
        // current time
        double t = 0;
        // number of snapshots
        int snapcount = 0;

        // plasma
        plasma sim_plasma;

    public:
        // constructor
        //@param in_X x length of the box
        //@param in_Y y length of the box
        //@param in_dx x grid size
        //@param in_dy y grid size
        //@param in_dt time step
        //@param n number of particle types
        //@param n_particles array with number of particles of each type (size n)
        //@param ctm array with charge to mass ratios for the particle types (size n)
        //@param f array of functionals for the distribution functions (size n by 4, 2 for position and 2 for velocity)
        //@param in_nFields number of fields (1 for electric, 2 for electromagnetic)
        //@param const_fields matrix with background fields (size in_nFields by 3)
        sim(double in_X, double in_Y, double in_dx, double in_dy, double in_dt, int n, int* n_particles, double* ctm, funcdouble** f, int in_nFields, double** const_fields);

        // set simulation name
        //@param new_name new name to give the simulation ("sim is default")
        void set_name(string new_name);
        // return simulation name
        string get_name();

        // get simulation fullname (timestamp + name)
        string get_fullname();

        // get a snapshot
        void snapshot();

        // run simulation
        //@param runtime total time to run
        //@param sc_dt time interval between snapshots
        void run(double runtime, double sc_dt);

};

#endif