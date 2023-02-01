#include "sim.h"
#include <filesystem>
#include <iostream>
#include <fstream>
#include <sstream>

sim::sim(double in_X, double in_Y, double in_dx, double in_dy, double in_dt, int n, int* n_particles, double* ctm, func** f, int in_nFields, double** const_fields) :
        X(in_X), Y(in_Y), dx(in_dx), dy(in_dy), dt(in_dt), sim_plasma(in_X, in_Y, in_dx, in_dy, n, n_particles, ctm, f, in_nFields, const_fields) {
}

void sim::set_name(string new_name) {
    name = new_name;
}

string sim::get_name() {
    return name;
}

void sim::snapshot() {
    ofstream f;
    stringstream ss;
    ss << "output/" << timestamp << "__" << name << "/" << snapcount << ".txt";
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

    f.close();

    snapcount++;
}

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
    f << "Ex= " << fields[0] << " Ey= " << fields[1] << " Bx= " << fields[2] << " By= " << fields[3] << endl;
    free(fields);
    f.close();

    snapcount = 0;
    double snap = t;
    snapshot();
    while (t < runtime + dt) {
        if (t - snap >= sc_dt) {
            snap = t;
            snapshot();
        }
        sim_plasma.move(dt);
        t += dt;
    }
}