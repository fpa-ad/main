#include "sim.h"
#include <filesystem>
#include <iostream>
#include <fstream>
#include <sstream>

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
sim::sim(double in_X, double in_Y, double in_dx, double in_dy, double in_dt, int n, int* n_particles, double* ctm, funcdouble** f, int in_nFields, double** const_fields) :
        X(in_X), Y(in_Y), dx(in_dx), dy(in_dy), dt(in_dt), sim_plasma(in_X, in_Y, in_dx, in_dy, n, n_particles, ctm, f, in_nFields, const_fields) {
}

// set simulation name
//@param new_name new name to give the simulation ("sim is default")
void sim::set_name(string new_name) {
    name = new_name;
}

// return simulation name
string sim::get_name() {
    return name;
}

// get simulation fullname (timestamp + name)
string sim::get_fullname() {
    return timestamp + string("__") + name;
}

// get a snapshot
void sim::snapshot() {
    ofstream f;
    stringstream ss;
    ss << "output/" << timestamp << "__" << name << "/" << setw(4) << setfill('0') << snapcount << ".txt";
    f.open (ss.str());

    int n = sim_plasma.get_n();
    f << t << " s " << n << " part. type(s)\n";

    particle** part = sim_plasma.get_particles();
    for (int i = 0; i < n; i++) {
        int n_part = sim_plasma.get_n_particle(i);
        f << part[i][0].get_ctm() << " [q/m] " << n_part << " particles\n";
        for (int j = 0; j < n_part; j++) {
            f << part[i][j].get_x() << " " << part[i][j].get_y() << " " << part[i][j].get_vx() << " " << part[i][j].get_vy() << endl;
        }
    }

    int Nx = (int)(X/dx);
    int Ny = (int)(Y/dy);

    f << "phi vals for the grid " << Nx << " by " << Ny << endl;

    for (int i = 0; i < Nx; i++) {
        for (int j = 0; j < Ny; j++) {
            f << sim_plasma.get_fields()[0].get_phi(i, j) << " ";
        }
        f << endl;
    }

    f.close();

    snapcount++;
}

// run simulation
//@param runtime total time to run
//@param sc_dt time interval between snapshots
void sim::run(double runtime, double sc_dt) {
    if (!filesystem::is_directory("output") || !filesystem::exists("output")) {
        filesystem::create_directory("output");
    }
    string folder = "output/" + timestamp + "__" + name;
    // this should not be a problem, but in case it is
    if (!filesystem::is_directory(folder) || !filesystem::exists(folder)) {
        filesystem::create_directory(folder);
    }

    ofstream f;
    f.open ("output/" + timestamp + "__" + name + "/README.txt");
    f << "Lx= " << X << " Ly= " << Y << " dx= " << dx << " dy= " << dy << " dt= " << dt << endl;
    int n = sim_plasma.get_n();
    f << n << " part. type(s)\n";
    particle** part = sim_plasma.get_particles();
    for (int i = 0; i < n; i++) {
        int n_part = sim_plasma.get_n_particle(i);
        f << part[i][0].get_ctm() << " [q/m] " << n_part << " particles\n";
    }
    double* fields = sim_plasma.get_background_fields();
    f << "Ex= " << fields[0] << " Ey= " << fields[1] << " Bz= " << fields[2] << endl;
    free(fields);
    f.close();

    snapcount = 0;
    double snap = t;
    snapshot();
    while (t < runtime + dt) {
        if (t - snap >= sc_dt) {
            snap = t;
            snapshot();
            cout<<"Simulation "<<t/runtime*100<<"\% Complete!\r"<<flush;
        }
        sim_plasma.move(dt);
        t += dt;
    }
    cout<<endl;
}
