#include "sim.h"
#include <cmath>

using namespace std;
 
double maxwellian(double x){
    double sigma=1;
    return exp(-x*x/(2*sigma*sigma))/(sigma*sqrt(2*M_PI));
}

double uniform(double x){
    return exp(-x*x);
}

int main()
{
    //Testing
    cout<<maxwellian(-2)<<endl;
    cout<<Integral(&maxwellian,-100,0,0.001)<<endl;
    cout<<InverseCDF(&maxwellian,0.5)<<endl;
    //EndTesting

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
    funcdouble** f=new funcdouble*[2];
    f[0]=new funcdouble[4];
    f[1]=new funcdouble[4];
    f[0][0]=&maxwellian;
    f[0][1]=&maxwellian;
    f[0][2]=&maxwellian;
    f[0][3]=&maxwellian;
    f[1][0]=&maxwellian;
    f[1][1]=&maxwellian;
    f[1][2]=&maxwellian;
    f[1][3]=&maxwellian;
    cout << "starting simulation" << endl;
    sim simulation(1, 1, 0.1, 0.1, 1e-3, 2, n_particles, ctm, f, 1, fields);
    cout << "running simulation" << endl;
    simulation.run(3, 0.05);
    cout << "simulation complete" << endl;
}