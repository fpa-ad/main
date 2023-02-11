#include "interface.h"
#include <math.h>
#include <functional>

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
py::str interface::create_simulation(double in_X, double in_Y, double in_dx, double in_dy, double in_dt, int in_n, py::list in_n_particles, py::list in_ctm, py::list in_f, int in_nFields, py::list in_const_fields) {
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

    if (nFields > 0) {
        const_fields = new double*[nFields];
        for (int i = 0; i < in_nFields; i++) {
            const_fields[i] = new double[3];
            for (int j = 0; j < 3; j++) {
                const_fields[i][j] = in_const_fields[i].cast<py::list>()[j].cast<double>();
            }
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
                    f[p][i] = (std::function<double(double)>) [L] (double x) {
                        if(x<-1000) return 1.;
                        return 1/L;
                    };
                    break;
                    }
                case 1:
                    {
                    // it's step
                    double L = (i == 0 ? in_X : in_Y);
                    double s = specs[1].cast<double>();
                    cout << "step starting at " << s << endl;
                    f[p][i] = (std::function<double(double)>) [s, L] (double x) {
                        if(x<-1000) return s+1; 
                        if (x < s)
                            return 0.0;
                        else
                            return 1/(L-s);
                    };
                    break;
                    }
                case 2:
                    {
                    // it's rectangular
                    double s = specs[1].cast<double>();
                    double e = specs[2].cast<double>();
                    cout << "rectangular starting at " << s << " and ending at " << e << endl;
                    f[p][i] = (std::function<double(double)>) [s, e] (double x) {
                        if(x<-1000) return ((s+e)/2); 
                        if (x < s)
                            return 0.0;
                        else if (x < e)
                            return 1/(e-s);
                        else
                            return 0.0;
                    };
                    break;
                    }
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
                    double v0 = specs[2].cast<double>();
                    cout << "maxwellian with vp " << vp << endl;
                    f[p][i] = (std::function<double(double)>) [vp, v0] (double v) {
                        if (abs(v) < 1000)
                            return 1/(vp*sqrt(M_PI)) * exp(-(v-v0)*(v-v0)/(vp*vp));
                        else
                            return v0+vp/10;
                        };
                    break;
                    }
                case 1:
                    {
                    // it's a bump-on-tail
                    double vp = specs[1].cast<double>();
                    double v0 = specs[2].cast<double>();
                    double b = specs[3].cast<double>();
                    cout << "bump-on-tail with vp " << vp << " at " << v0 << " with b= " << b << endl;
                    f[p][i] = (std::function<double(double)>) [vp, v0, b] (double v) {
                        if (abs(v) < 1000)
                            return 1/(vp*sqrt(M_PI)) * ((1-b)*exp(-v*v/(vp*vp)) + b*exp(-(v-v0)*(v-v0)/(vp*vp))) ;
                        else
                            return vp/10;
                        };
                    break;
                    }
            }
        }
    }

    my_sim = new sim(in_X, in_Y, in_dx, in_dy, in_dt, n, n_particles, ctm, f, in_nFields, const_fields);
    
    return (py::str) my_sim->get_fullname();

}

// run the simulation
//@param runtime total time to run
//@param sc_dt time interval between snapshots
void interface::run_simulation(double runtime, double sc_dt) {
    my_sim->run(runtime, sc_dt);
}

// end the simulation (basically a destructor)
void interface::end_simulation() {
    delete n_particles;
    n_particles = nullptr;
    delete ctm;
    ctm = nullptr;
    for (int i = 0; i < nFields; i++) {
        delete const_fields[i];
    }
    delete const_fields;
    const_fields = nullptr;
    // TODO deleting f does not work

}