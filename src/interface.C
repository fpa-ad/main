#include "interface.h"

void interface::create_simulation(double in_X, double in_Y, double in_dx, double in_dy, double in_dt, int n, py::list in_n_particles, py::list in_ctm, py::list in_f, int in_nFields, py::list in_const_fields) {
    int* n_particles = (int*) malloc(n*sizeof(int));
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

    // go through the functions for the positions
    for (int i = 0; i < 2; i++) {
        py::list specs = in_f[i].cast<py::list>();
        switch (specs[0].cast<int>()) {
            case 0:
                // it's uniform
                cout << "uniform" << endl;
                break;
            case 1:
                // it's step
                cout << "step starting at " << specs[1].cast<double>() << endl;
                break;
            case 2:
                // it's plateau
                cout << "plateau starting at " << specs[1].cast<double>() << " and ending at " << specs[2].cast<double>() << endl;
                break;
        }
    }

    // go through the functions for the velocities
    for (int i = 2; i < 4; i++) {
        py::list specs = in_f[i].cast<py::list>();
        switch (specs[0].cast<int>()) {
            case 0:
                // it's maxwellian
                cout << "maxwellian with T " << specs[1].cast<double>() << endl;
                break;
            case 1:
                // it's a bump-on-tail
                cout << "bump-on-tail at " << specs[1].cast<double>() << " with a= " << specs[2].cast<double>() << endl;
        }
    }

    my_sim = new sim(in_X, in_Y, in_dx, in_dy, in_dt, n, n_particles, ctm, nullptr, in_nFields, const_fields);
}