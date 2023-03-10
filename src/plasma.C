#include "plasma.h"
#include <cstdlib>
#include <random>

// constructor
//@param in_X x length of the box
//@param in_Y y length of the box
//@param in_dx x grid size
//@param in_dy y grid size
//@param in_dt time step
//@param n number of particle types
//@param n_particles array with number of particles of each type (size n)
//@param ctm array with charge to mass ratios for the particle types (size n)
//@param f array of functionals for the distribution functions (size n by 4, 2 for position and 2 for velocity)
//@param in_nFields number of fields (1 for electric, 2 for electromagnetic)
//@param const_fields matrix with background fields (size in_nFields by 3)
plasma::plasma(double in_Lx, double in_Ly, double in_hx, double in_hy, int in_n, int* in_n_particles, double* in_ctm, funcdouble** f, int in_nFields, double** const_fields) : Lx(in_Lx), Ly(in_Ly), hx(in_hx), hy(in_hy), n(in_n), n_particles(in_n_particles), ctm(in_ctm), nFields(in_nFields), bkg_fields(const_fields) {

    // initialize particles
    particles = (particle**) malloc(n*sizeof(particle*));
    // for each particle type
    for (int i = 0; i < n; i++) {
        // create the particle array
        particles[i] = (particle*) malloc(n_particles[i] * sizeof(particle));
        // copy the ctm ratios to properly store them
        ctm[i] = in_ctm[i];
        // loop through the particles

        random_device rd;  // Will be used to obtain a seed for the random number engine
        mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()

        for (int j = 0; j < n_particles[i]; j++) {
            // f[i] should be an array of four functions to initialize the x y vx and vy coordinates
            double raux1=(double)(gen())/((double)(gen.max()));
            double raux2=(double)(gen())/((double)(gen.max()));
            double raux3=(double)(gen())/((double)(gen.max()));
            double raux4=(double)(gen())/((double)(gen.max()));
            particles[i][j] = particle(ctm[i], InverseCDF_X(f[i][0],raux1), InverseCDF_X(f[i][1],raux2), InverseCDF_V2(f[i][2],raux3), InverseCDF_V2(f[i][3],raux4));
            particles[i][j].sanity_check(Lx,Ly);
            cout<<"Particle "<<i<<" Initialization "<<(((double)(j))/n_particles[i]*100)<<"\% Complete!\r"<<flush;
        }
        cout<<endl;
    }

    //initialize fields
    fields = (Field*) malloc(nFields*sizeof(fields[0]));
    //loop through fields
    if(nFields>0) fields[0] = Field(Lx, Ly, hx, hy, const_fields[0][0], const_fields[0][1], const_fields[0][2]);
    if(nFields>1) fields[1] = Field(Lx, Ly, hx, hy, const_fields[1][0], const_fields[1][1], const_fields[1][2]);

    //// TEST ///
    //cout<<ctm[0]<<endl;
    /////////////
}

// destructor
plasma::~plasma() {
    for (int i = 0; i < n; i++) {
        free(particles[i]);
    }
    free(particles);
    free(fields);
}

// return how many particle types
int plasma::get_n() {
    return n;
}

// return how many of the i-th particle type (no validation)
//@param i index of the particle type
int plasma::get_n_particle(int i) {
    return n_particles[i];
}

// return the particle matrix
particle** plasma::get_particles() {
    return particles;
}

// return the background fields array (E_x, E_y, B_z)
double* plasma::get_background_fields() {
    double* f = (double*) malloc(3*sizeof(double));
    if (nFields <= 1) {
        f[2] = 0;
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
    }
    return f;
}

// return the field object array
Field* plasma::get_fields() {
    return fields;
}

// get the Ex field for a given position
//@param x x position, from 0 to Lx
//@param y y position, from 0 to Ly
double plasma::get_Ex(double x, double y) {
    if (nFields == 0) {
        return 0;
    }
    else {
        return fields[0].get_X(x, y);
    }
}

// get the Ey field for a given position
//@param x x position, from 0 to Lx
//@param y y position, from 0 to Ly
double plasma::get_Ey(double x, double y) {
    if (nFields == 0) {
        return 0;
    }
    else {
        return fields[0].get_Y(x, y);
    }
}

// get the Ez field for a given position
//@param x x position, from 0 to Lx
//@param y y position, from 0 to Ly
double plasma::get_Ez(double x, double y) {
    if (nFields == 0) {
        return 0;
    }
    else {
        return fields[0].get_Z(x, y);
    }
}

// get the Bx field for a given position
//@param x x position, from 0 to Lx
//@param y y position, from 0 to Ly
double plasma::get_Bx(double x, double y) {
    if (nFields <= 1) {
        return 0;
    }
    else {
        return fields[1].get_X(x, y);
    }
}

// get the By field for a given position
//@param x x position, from 0 to Lx
//@param y y position, from 0 to Ly
double plasma::get_By(double x, double y) {
    if (nFields <= 1) {
        return 0;
    }
    else {
        return fields[1].get_Y(x, y);
    }
}

// get the Bz field for a given position
//@param x x position, from 0 to Lx
//@param y y position, from 0 to Ly
double plasma::get_Bz(double x, double y) {
    if (nFields <= 1) {
        return 0;
    }
    else {
        return fields[1].get_Z(x, y);
    }
}

// move - calculate the next iteration
//@param dt time step
void plasma::move(double dt) {
    // loop through the particles
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n_particles[i]; j++) {
            double x = particles[i][j].get_x();
            double y = particles[i][j].get_y();
            particles[i][j].advance_position(dt, get_Ex(x, y), get_Ey(x, y), get_Ez(x, y), get_Bx(x, y), get_By(x, y), get_Bz(x, y));
            particles[i][j].sanity_check(Lx,Ly);
        }
    }
    // update the fields
    for (int i = 0; i < 1/*nFields*/; i ++) {
        fields[i].Update(n, n_particles, ctm, particles);
    }
    // loop through the particles
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n_particles[i]; j++) {
            double x = particles[i][j].get_x();
            double y = particles[i][j].get_y();
            particles[i][j].advance_velocity(dt, get_Ex(x, y), get_Ey(x, y), get_Ez(x, y), get_Bx(x, y), get_By(x, y), get_Bz(x, y));
            particles[i][j].sanity_check(Lx, Ly);
        }
    }
}