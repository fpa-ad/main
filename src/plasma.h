#ifndef __PLASMA__
#define __PLASMA__

#include "particle.h"

using namespace std;

class plasma{
    private:
        // how many particle types
        int n = 0;
        // how many of each particle
        int* n_particles = nullptr;
        // particle matrix (first index por particle type, second index for particle itself)
        particle** particles = nullptr;

        // Field

    public:
        // constructor
        plasma(int in_n, int* in_n_particles, int* ctm, auto f);

        // move
        move(double dt);

        // destructor
        ~plasma();
};

#endif