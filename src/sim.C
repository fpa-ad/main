#include "sim.h"

sim::sim(double in_X, double in_Y, double in_dx, double in_dy, double in_dt, int n, int* n_particles, int* ctm, auto f) :
        X(in_X), Y(in_Y), dx(in_dx), dy(in_dy), dt(in_dt) {
    *sim_plasma = plasma(n, n_particles, ctm, f);
};