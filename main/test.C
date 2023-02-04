#include "sim.h"
#include <cmath>

using namespace std;
 
double maxwellian(double x){
    double temp=0.2;
    double sigma=sqrt(temp);
    return exp(-x*x/(2*sigma*sigma))/(sigma*sqrt(2*M_PI));
}

double uniform(double x){
    double L=10;
    if(x>0&&x<L) return 1/L;
    return 0;
}

int main(){

    int n_particles[2];
    n_particles[0] = 100;
    n_particles[1] = 100;
    double ctm[2];
    ctm[0] = 1;
    ctm[1] = -1;
    double** fields = new double*[2];
    fields[0] = new double[3];
    fields[1] = new double[3];
    fields[0][0] = 0;
    fields[0][1] = 0;
    fields[0][2] = 0;
    fields[1][0] = 0;
    fields[1][1] = 0;
    fields[1][2] = 10;
    funcdouble** f=new funcdouble*[2];
    f[0]=new funcdouble[4];
    f[1]=new funcdouble[4];
    f[0][0]=&uniform;
    f[0][1]=&uniform;
    f[0][2]=&maxwellian;
    f[0][3]=&maxwellian;
    f[1][0]=&uniform;
    f[1][1]=&uniform;
    f[1][2]=&maxwellian;
    f[1][3]=&maxwellian;
    cout << "starting simulation" << endl;
    sim simulation(10, 10, 0.2, 0.2, 1e-3, 2, n_particles, ctm, f, 1, fields);
    cout << "running simulation" << endl;
    simulation.run(5, 0.05);
    cout << "simulation complete" << endl;
}