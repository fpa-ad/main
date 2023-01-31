#ifndef __PLASMA__
#define __PLASMA__

#include "Particle.h"
#include "Field.h"

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
        int nFields=0;
        // vector of field objects
        Field* fields = nullptr;
        // background fields;
        double** bkg_fields = nullptr;

        //properties of grid
        //Size of box
        double Lx;
        double Ly;
        //Spatial Step
        double hx;
        double hy;

    public:
        // constructor
        plasma(double in_Lx, double in_Ly, double in_hx, double in_hy, int in_n, int* in_n_particles, double* in_ctm, auto f, int in_nFields, double** const_fields);

        int get_n();
        int get_n_particle(int i);
        particle** get_particles();
        double* get_background_fields();

        double get_Ex(double x, double y);
        double get_Ey(double x, double y);
        double get_Bx(double x, double y);
        double get_By(double x, double y);

        // move
        void move(double dt);

        // destructor
        ~plasma();
};

#endif