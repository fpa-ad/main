#include "plasma.h"
#include <cstdlib>

// constructor
plasma::plasma(int in_n, int* in_n_particles, int* ctm, auto f) {
    n = in_n;
    n_particles = in_n_particles;
    particles = (particle**) malloc(sizeof(particle*));
    // for each particle type
    for (i = 0; i < n, i++) {
        // create the particle array
        particles[i] = (particle*) malloc(sizeof(particle));
        // loop through the particles
        for (j = 0; j < n_particles[i]; j++) {
            // f[i] should be an array of four functions to initialize the x y vx and vy coordinates
            particle_array[j] = particle(ctm[i], f[i][0](), f[i][1](), f[i][2](), f[i][3]());
        }
    }
}

// destructor
plasma::~plasma() {
    for (i = 0; i < n; i++) {
        free(particles[i])
    }
    free(particles)
}