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
    fields = new Field[nFields];
    //loop through fields
    for (int i = 0; i < nFields; i++){
        fields[i]=Field(Lx, Ly, hx, hy, const_fields[i][0], const_fields[i][1]);
    }
};

// move
plasma::move(double dt) {
    // loop through the particles
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n_particles[i]; j++) {
            // advance
        }
    }
}

// destructor
plasma::~plasma() {
    for (int i = 0; i < n; i++) {
        free(particles[i]);
    }
    free(particles);
};