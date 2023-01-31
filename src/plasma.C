#include "plasma.h"
#include <cstdlib>

// constructor
plasma::plasma(double in_Lx, double in_Ly, double in_hx, double in_hy, int in_n, int* in_n_particles, int* ctm, auto f, int in_nFields, double** const_fields) : Lx(in_Lx),Ly(in_Ly),hx(in_hx),hy(in_hy),n(in_n), n_particles(in_n_particles) , nFields(in_nFields) {

    //initialize particles
    particles = (particle**) malloc(sizeof(particle*));
    // for each particle type
    for (int i = 0; i < n; i++) {
        // create the particle array
        particles[i] = (particle*) malloc(sizeof(particle));
        // loop through the particles
        for (int j = 0; j < n_particles[i]; j++) {
            // f[i] should be an array of four functions to initialize the x y vx and vy coordinates
            particles[i][j] = particle(ctm[i], f[i][0](), f[i][1](), f[i][2](), f[i][3]());
        }
    }

    //initialize fields
    fields = (Field*) malloc(sizeof(Field));
    //loop through fields
    for (int i = 0; i < nFields; i++){
        fields[i]=Field(Lx, Ly, hx, hy, const_fields[i][0], const_fields[i][1]);
    }
};

inline int plasma::get_n() {
    return n;
};

inline int plasma::get_n_particle(int i) {
    return n_particles[i];
};

inline particle** plasma::get_particles() {
    return particles;
};

inline double plasma::get_Ex(double x, double y) {
    if (nFields == 0) {
        return 0;
    }
    else {
        return fields[0].get_X(x, y);
    }
};

inline double plasma::get_Ey(double x, double y) {
    if (nFields == 0) {
        return 0;
    }
    else {
        return fields[0].get_Y(x, y);
    }
};

inline double plasma::get_Bx(double x, double y) {
    if (nFields <= 1) {
        return 0;
    }
    else {
        return fields[1].get_X(x, y);
    }
};

inline double plasma::get_By(double x, double y) {
    if (nFields <= 1) {
        return 0;
    }
    else {
        return fields[1].get_Y(x, y);
    }
};

// move
void plasma::move(double dt) {
    // loop through the particles
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n_particles[i]; j++) {
            double x = particles[i][j].get_x();
            double y = particles[i][j].get_y();
            particles[i][j].advance_position(dt, get_Ex(x, y), get_Ey(x, y), get_Bx(x, y), get_By(x, y));
        }
    }
};

// destructor
plasma::~plasma() {
    for (int i = 0; i < n; i++) {
        free(particles[i]);
    }
    free(particles);
};