#include <pybind11/pybind11.h>
#include "sim.h"

namespace py = pybind11;

using namespace pybind11::literals;

class interface {
    private:
        sim* my_sim;

    public:
        interface() {};
        ~interface() {};

        void create_simulation(double in_X, double in_Y, double in_dx, double in_dy, double in_dt, int n, py::list in_n_particles, py::list in_ctm, py::list in_f, int in_nFields, py::list in_const_fields);
        void run_simulation(double runtime, double sc_dt);
};