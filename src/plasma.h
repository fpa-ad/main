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
        // particle matrix (first index for particle type, second index for particle itself)
        particle** particles = nullptr;
        
        // number of fields
        int nFields=0;
        // vector of field objects
        Field* fields = nullptr;

        //properties of grid
        //Size of box
        double Lx;
        double Ly;
        //Spatial Step
        double hx;
        double hy;

    public:
        // constructor
        plasma(double in_Lx, double in_Ly, double in_hx, double in_hy, int in_n, int* in_n_particles, int* ctm, auto f, int in_nFields, double** const_fields);

        inline int get_n();
        inline int get_n_particle(int i);
        inline particle** get_particles();

        inline double get_Ex(double x, double y);
        inline double get_Ey(double x, double y);
        inline double get_Bx(double x, double y);
        inline double get_By(double x, double y);

        // move
        void move(double dt);

        // destructor
        ~plasma();
};

#endif