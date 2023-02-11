#include <pybind11/pybind11.h>
#include "sim.h"

namespace py = pybind11;

using namespace pybind11::literals;

class interface {
    private:
        // simulation object
        sim* my_sim;
        // how many particle types
        int n;
        // how many of each particle
        int* n_particles;
        // array of distribution functions
        funcdouble** f;
        // charge to mass ratios
        double* ctm;
        // number of fields
        int nFields;
        // background fields
        double** const_fields;

    public:
        // constructor
        interface() {};

        // destructor
        ~interface() {end_simulation();};

        // create the simulation
        //@param in_X x length of the box
        //@param in_Y y length of the box
        //@param in_dx x grid size
        //@param in_dy y grid size
        //@param in_dt time step
        //@param n number of particle types
        //@param n_particles array with number of particles of each type (size n)
        //@param in_ctm array with charge to mass ratios for the particle types (size n)
        //@param in_f array of functionals for the distribution functions (size n by 4, 2 for position and 2 for velocity)
        //@param in_nFields number of fields (1 for electric, 2 for electromagnetic)
        //@param in_const_fields matrix with background fields (size in_nFields by 3)
        py::str create_simulation(double in_X, double in_Y, double in_dx, double in_dy, double in_dt, int n, py::list in_n_particles, py::list in_ctm, py::list in_f, int in_nFields, py::list in_const_fields);

        // run the simulation
        //@param runtime total time to run
        //@param sc_dt time interval between snapshots
        void run_simulation(double runtime, double sc_dt);

        // end the simulation (basically a destructor)
        void end_simulation();
};