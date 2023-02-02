#include "sim.h"

using namespace std;
 
int main()
{
    int n_particles[2];
    n_particles[0] = 10;
    n_particles[1] = 10;
    double ctm[2];
    ctm[0] = 1;
    ctm[1] = -1;
    double** fields = new double*[1];
    fields[0] = new double[2];
    fields[0][0] = 1;
    fields[0][1] = 0;
    cout << "starting simulation" << endl;
    sim simulation(1, 1, 0.1, 0.1, 1e-3, 2, n_particles, ctm, nullptr, 1, fields);
    cout << "running simulation" << endl;
    simulation.run(1, 0.05);
    cout << "simulation complete" << endl;
}