#ifndef __PLASMA__
#define __PLASMA__

#include "particle.h"
#include "Field.h"
#include "myutils.h"
#include <iostream>

using namespace std;

class plasma{
    private:
        // how many particle types
        int n = 0;
        // how many of each particle
        int* n_particles = nullptr;
        // charge to mass ratios
        double* ctm = nullptr;
        // particle matrix (first index for particle type, second index for particle itself)
        particle** particles = nullptr;
        
        // number of fields
        int nFields = 0;
        // background fields;
        double** bkg_fields = nullptr;
        // vector of field objects
        Field* fields = nullptr;

        // size of box - x direction
        double Lx;
        // size of box - y direction
        double Ly;
        // spatial step - x direction
        double hx;
        // spatial step - y direction
        double hy;

    public:
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
        plasma(double in_Lx, double in_Ly, double in_hx, double in_hy, int in_n, int* in_n_particles, double* in_ctm, funcdouble** f, int in_nFields, double** const_fields);
        
        // destructor
        ~plasma();

        // return how many particle types
        int get_n();
        // return how many of the i-th particle type (no validation)
        //@param i index of the particle type
        int get_n_particle(int i);
        // return the particle matrix
        particle** get_particles();
        // return the background fields array (E_x, E_y, B_z)
        double* get_background_fields();
        // return the field object array
        Field* get_fields();

        // get the Ex field for a given position
        //@param x x position, from 0 to Lx
        //@param y y position, from 0 to Ly
        double get_Ex(double x, double y);
        // get the Ey field for a given position
        //@param x x position, from 0 to Lx
        //@param y y position, from 0 to Ly
        double get_Ey(double x, double y);
        // get the Ez field for a given position
        //@param x x position, from 0 to Lx
        //@param y y position, from 0 to Ly
        double get_Ez(double x, double y);
        // get the Bx field for a given position
        //@param x x position, from 0 to Lx
        //@param y y position, from 0 to Ly
        double get_Bx(double x, double y);
        // get the By field for a given position
        //@param x x position, from 0 to Lx
        //@param y y position, from 0 to Ly
        double get_By(double x, double y);
        // get the Bz field for a given position
        //@param x x position, from 0 to Lx
        //@param y y position, from 0 to Ly
        double get_Bz(double x, double y);

        // move - calculate the next iteration
        //@param dt time step
        void move(double dt);
};

#endif