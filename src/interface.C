#include "interface.h"
#include <math.h>
#include <functional>

void interface::create_simulation(double in_X, double in_Y, double in_dx, double in_dy, double in_dt, int in_n, py::list in_n_particles, py::list in_ctm, py::list in_f, int in_nFields, py::list in_const_fields) {
    n = in_n;
    
    n_particles = new int[n];
    for (int i = 0; i < n; i++) {
        n_particles[i] = in_n_particles[i].cast<double>();
    }

    ctm = new double[n];
    for (int i = 0; i < n; i++) {
        ctm[i] = in_ctm[i].cast<double>();
    }

    nFields = in_nFields;

    const_fields = new double*[nFields];
    for (int i = 0; i < in_nFields; i++) {
        const_fields[i] = new double[3];
        for (int j = 0; j < 3; j++) {
            const_fields[i][j] = in_const_fields[i].cast<py::list>()[j].cast<double>();
        }
    }

    f = new funcdouble*[n];

    for (int p = 0; p < n; p++) {

        f[p] = new funcdouble[4];
        
        // go through the functions for the positions

        py::list fp = in_f[p].cast<py::list>();

        for (int i = 0; i < 2; i++) {
            py::list specs = fp[i].cast<py::list>();
            switch (specs[0].cast<int>()) {
                case 0:
                    {
                    // it's uniform
                    cout << "uniform" << endl;
                    double L = (i == 0 ? in_X : in_Y);
                    f[p][i] = (std::function<double(double)>) [L] (double x) {return 1/L;};
                    break;
                    }
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
            py::list specs = fp[i].cast<py::list>();
            switch (specs[0].cast<int>()) {
                case 0:
                    {
                    // it's maxwellian
                    double vp = specs[1].cast<double>();
                    cout << "maxwellian with vp " << vp << endl;
                    f[p][i] = (std::function<double(double)>) [vp] (double v) {return 1/(vp*sqrt(M_PI)) * exp(-v*v/(vp*vp));};
                    break;
                    }
                case 1:
                    // it's a bump-on-tail
                    cout << "bump-on-tail with vp " << specs[1].cast<double>() << " at " << specs[2].cast<double>() << " with a= " << specs[3].cast<double>() << endl;
            }
        }
    }

    my_sim = new sim(in_X, in_Y, in_dx, in_dy, in_dt, n, n_particles, ctm, f, in_nFields, const_fields);

}

void interface::end_simulation() {
    delete n_particles;
    delete ctm;
    for (int i = 0; i < nFields; i++) {
        delete const_fields[i];
    }
    delete const_fields;
    // TODO deleting f does not work.

}

void interface::run_simulation(double runtime, double sc_dt) {
    my_sim->run(runtime, sc_dt);
}