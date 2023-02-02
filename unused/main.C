#include "sim.h"
#include "myutils.h"

using namespace std;
 
int main()
{
    int n_particles[1];
    n_particles[0] = 1;
    double ctm[1];
    ctm[0] = -1;
    func** arr = (func**) malloc(sizeof(func*));
    arr[0] = (func*) malloc(4*sizeof(func));
    arr[0][0] = &(random_pos);
    arr[0][1] = &(random_pos);
    arr[0][2] = &(random_speed);
    arr[0][3] = &(random_speed);
    sim simulation(1, 1, 0.1, 0.1, 0.01, 1, n_particles, ctm, arr);
}
