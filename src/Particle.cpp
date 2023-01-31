#include "particle.h"

// constructor
particle::particle(double in_ctm, double in_x, double in_y, double in_vx, double in_vy) {
    ctm = in_ctm;
    x = in_x;
    y = in_y;
    vx = in_vx;
    vy = in_vy;
}

// advance function - steps 1 and 2
void Particle::advance_position(double dt, double Ex, double Ey, double Bx, double By) {
    vx += ctm/2 * dt * Ex;
    x += dt * vx;
}

// advance function - step 3
void Particle::advance_velocity(double dt, double Ex, double Ey, double Bx, double By) {
    vx += ctm/2 * dt * Ex;
}