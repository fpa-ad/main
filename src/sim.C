#include "sim.h"
#include <filesystem>
#include <iostream>
#include <fstream>

sim::sim(double in_X, double in_Y, double in_dx, double in_dy, double in_dt, int n, int* n_particles, int* ctm, auto f) :
        X(in_X), Y(in_Y), dx(in_dx), dy(in_dy), dt(in_dt) {
    *sim_plasma = plasma(n, n_particles, ctm, f);
};

sim::set_name(string new_name) {
    name = new_name;
}

sim::get_name() {
    return name;
}

sim::snapshot() {
    ofstream f;
    f.open (timestamp + "--" + name + string(snapcount) + ".txt");

    n = sim_plasma->get_n();
    f << t << " s " << n << " part. types\n";

    part = sim_plasma->get_particles();
    for (int i = 0; i < n; i++) {
        n_part = sim_plasma->get_n_particle(i);
        f << part[i][0].get_ctm() << " [q/m] " << n_part << " particles\n";
    }

    f.close();

    snapcount++;
}

void sim::run(double runtime, double sc_dt) {
    folder = timestamp + "--" + name;
    // this should not be a problem, but in case it is
    if (!fs::is_directory(folder) || !fs::exists(folder)) {
        fs::create_directory(folder);
    }
    snapcount = 0;
    snap = t;
    snapshot();
    while (t < runtime) {
        if (t - start) > sc_dt {
            snap = t;
            snapshot();
        }
        sim_plasma->move(dt);
        t += dt;
    }
}