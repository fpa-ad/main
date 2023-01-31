#include "Particle.h"

// constructor
particle::particle(double in_ctm, double in_x, double in_y, double in_vx, double in_vy) :
                    ctm(in_ctm), x(in_x), y(in_y), vx(in_vx), vy(in_vy) {};

double particle::get_ctm() {
    inline return ctm;
}

double particle::get_x() {
    inline return x;
}

double particle::get_y() {
    inline return y;
}

double particle::get_vx() {
    inline return vx;
}

double particle::get_vy() {
    inline return vy;
}

// advance function - steps 1 and 2
void particle::advance_position(double dt, double Ex, double Ey, double Bx, double By) {
    vx += ctm/2 * dt * Ex;
    x += dt * vx;
};

// advance function - step 3
void particle::advance_velocity(double dt, double Ex, double Ey, double Bx, double By) {
    vx += ctm/2 * dt * Ex;
};