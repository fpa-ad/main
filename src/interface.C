#include "interface.h"

void interface::create_simulation(double in_X, double in_Y, double in_dx, double in_dy, double in_dt, int n, py::list in_n_particles, py::list in_ctm, py::list in_f, int in_nFields, py::list in_const_fields) {
    double* n_particles = (double*) malloc(n*sizeof(double));
    for (int i = 0; i < n; i++) {
        n_particles[i] = in_n_particles[i].cast<double>();
    }

    double* ctm = (double*) malloc(n*sizeof(double));
    for (int i = 0; i < n; i++) {
        ctm[i] = in_ctm[i].cast<double>();
    }

    double** const_fields = (double**) malloc(in_nFields*sizeof(double*));
    for (int i = 0; i < in_nFields; i++) {
        const_fields[i] = (double*) malloc(3*sizeof(double));
        for (int j = 0; j < 3; j++) {
            const_fields[i][j] = in_const_fields[i].cast<py::list>()[j].cast<double>();
        }
    }
}