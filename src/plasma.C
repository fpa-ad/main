#include "plasma.h"
#include <cstdlib>

// constructor
plasma::plasma(double in_Lx, double in_Ly, double in_hx, double in_hy, int in_n, int* in_n_particles, double* in_ctm, func** f, int in_nFields, double** const_fields) : Lx(in_Lx), Ly(in_Ly), hx(in_hx), hy(in_hy), n(in_n), n_particles(in_n_particles), nFields(in_nFields), bkg_fields(const_fields) {

    // initialize particles
    particles = (particle**) malloc(n*sizeof(particle*));
    // initialize ctm ratios
    ctm = (double*) malloc(sizeof(n*sizeof(double)));
    // for each particle type
    for (int i = 0; i < n; i++) {
        // create the particle array
        particles[i] = (particle*) malloc(n_particles[i] * sizeof(particle));
        // copy the ctm ratios to properly store them
        ctm[i] = in_ctm[i];
        // loop through the particles
        for (int j = 0; j < n_particles[i]; j++) {
            // f[i] should be an array of four functions to initialize the x y vx and vy coordinates
            // particles[i][j] = particle(ctm[i], f[i][0](), f[i][1](), f[i][2](), f[i][3]());
            particles[i][j] = particle(ctm[i], 0.5, 0.5, 1, 0);
        }
    }

    //initialize fields
    fields = (Field*) malloc(nFields * sizeof(Field));
    //loop through fields
    for (int i = 0; i < nFields; i++){
        fields[i] = Field(Lx, Ly, hx, hy, const_fields[i][0], const_fields[i][1]);
    }
}

int plasma::get_n() {
    return n;
}

int plasma::get_n_particle(int i) {
    return n_particles[i];
}

particle** plasma::get_particles() {
    return particles;
}

double* plasma::get_background_fields() {
    double* f = (double*) malloc(4*sizeof(double));
    if (nFields <= 1) {
        f[3] = f[2] = 0;
        if (nFields == 1) {
            f[0] = bkg_fields[0][0];
            f[1] = bkg_fields[0][1];
        }
        else {
            f[1] = f[0] = 0;
        }
    }
    else {
        f[2] = bkg_fields[1][0];
        f[3] = bkg_fields[1][1];
    }
    return f;
}

double plasma::get_Ex(double x, double y) {
    if (nFields == 0) {
        return 0;
    }
    else {
        return fields[0].get_X(x, y);
    }
}

double plasma::get_Ey(double x, double y) {
    if (nFields == 0) {
        return 0;
    }
    else {
        return fields[0].get_Y(x, y);
    }
}

double plasma::get_Bx(double x, double y) {
    if (nFields <= 1) {
        return 0;
    }
    else {
        return fields[1].get_X(x, y);
    }
}

double plasma::get_By(double x, double y) {
    if (nFields <= 1) {
        return 0;
    }
    else {
        return fields[1].get_Y(x, y);
    }
}

// move
void plasma::move(double dt) {
    // loop through the particles
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n_particles[i]; j++) {
            cout << "getting x" << endl;
            double x = particles[i][j].get_x();
            cout << "getting y" << endl;
            double y = particles[i][j].get_y();
            cout << "advancing position" << endl;
            particles[i][j].advance_position(dt, get_Ex(x, y), get_Ey(x, y), get_Bx(x, y), get_By(x, y));
        }
    }
    // update the fields
    for (int i = 0; i < nFields; i ++) {
        fields[i].Update(fields[i].Density(n, n_particles, ctm, particles));
    }
    // loop through the particles
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n_particles[i]; j++) {
            double x = particles[i][j].get_x();
            double y = particles[i][j].get_y();
            particles[i][j].advance_velocity(dt, get_Ex(x, y), get_Ey(x, y), get_Bx(x, y), get_By(x, y));
            particles[i][j].sanity_check(Lx, Ly);
        }
    }
}

// destructor
plasma::~plasma() {
    for (int i = 0; i < n; i++) {
        free(particles[i]);
    }
    free(particles);
    free(ctm);
}