#include "particle.h"
#include <iostream>

// constructor
//@param in_ctm charge to mass ratio
//@param in_x starting x position
//@param in_y starting y position
//@param in_vx starting x velocity
//@param in_vy starting y velocity
particle::particle(double in_ctm, double in_x, double in_y, double in_vx, double in_vy) :
                    ctm(in_ctm), x(in_x), y(in_y), vx(in_vx), vy(in_vy) {};

// return charge to mass ratio
double particle::get_ctm() {
    return ctm;
};

// return current x position
double particle::get_x() {
    return x;
};

// return current y position
double particle::get_y() {
    return y;
};

// return current x velocity
double particle::get_vx() {
    return vx;
};

// return current y velocity
double particle::get_vy() {
    return vy;
};

// advance function - Verlet steps 1 and 2
//@param dt time step
//@param Ex electric field at the particle's position, x direction
//@param Ey electric field at the particle's position, y direction
//@param Ez electric field at the particle's position, z direction
//@param Bx magnetic field at the particle's position, x direction
//@param By magnetic field at the particle's position, y direction
//@param Bz magnetic field at the particle's position, z direction
void particle::advance_position(double dt, double Ex, double Ey, double Ez, double Bx, double By, double Bz) {
    vx += ctm/2 * dt * (Ex + vy * Bz);
    vy += ctm/2 * dt * (Ey - vx * Bz); 
    x += dt * vx;
    y += dt * vy;
};

// advance function - Verlet step 3
//@param Ex electric field at the particle's position, x direction
//@param Ey electric field at the particle's position, y direction
//@param Ez electric field at the particle's position, z direction
//@param Bx magnetic field at the particle's position, x direction
//@param By magnetic field at the particle's position, y direction
//@param Bz magnetic field at the particle's position, z direction
void particle::advance_velocity(double dt, double Ex, double Ey, double Ez, double Bx, double By, double Bz) {
    vx += ctm/2 * dt * (Ex + vy * Bz);
    vy += ctm/2 * dt * (Ey - vx * Bz);
};

// thinking with portals: enabled (aka periodic border conditions)
//@param X x length of the box
//@param Y y length of the box
void particle::sanity_check(double X, double Y) {
    if (x > X) {
        x -= X;
        sanity_check(X, Y);
    }
    else if (x < 0) {
        x += X;
        sanity_check(X, Y);
    }
    if (y > Y) {
        y -= Y;
        sanity_check(X, Y);
    }
    else if (y < 0) {
        y += Y;
        sanity_check(X, Y);
    }
};