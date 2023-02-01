#include "Particle.h"
#include <iostream>

// constructor
particle::particle(double in_ctm, double in_x, double in_y, double in_vx, double in_vy) :
                    ctm(in_ctm), x(in_x), y(in_y), vx(in_vx), vy(in_vy) {};

double particle::get_ctm() {
    return ctm;
};

double particle::get_x() {
    return x;
};

double particle::get_y() {
    return y;
};

double particle::get_vx() {
    return vx;
};

double particle::get_vy() {
    return vy;
};

// advance function - steps 1 and 2
void particle::advance_position(double dt, double Ex, double Ey, double Bx, double By) {
    vx += ctm/2 * dt * Ex;
    x += dt * vx;
};

// advance function - step 3
void particle::advance_velocity(double dt, double Ex, double Ey, double Bx, double By) {
    vx += ctm/2 * dt * Ex;
};

void particle::sanity_check(double X, double Y) {
    if (x > X) {
        x -= X;
    }
    else if (x < X) {
        x += X;
    }
    if (y > Y) {
        y -= Y;
    }
    else if (y > Y) {
        y += Y;
    }
};