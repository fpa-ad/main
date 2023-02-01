#include "sim.h"

using namespace std;
 
int main()
{
    int n_particles[1];
    n_particles[0] = 10;
    double ctm[1];
    ctm[0] = -1;
    double** fields = new double*[1];
    fields[0] = new double[2];
    fields[0][0] = 1;
    fields[0][1] = 0;
    cout << "starting simulation" << endl;
    sim simulation(1, 1, 0.1, 0.1, 0.01, 1, n_particles, ctm, nullptr, 0, fields);
    cout << "running simulation" << endl;
    simulation.run(1, 0.5);
}