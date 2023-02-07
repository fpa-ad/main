#include "sim.h"
#include <cmath>

using namespace std;
 
double maxwellian(double x){
    double temp=1;
    double sigma=sqrt(temp);
    if (x<-1000) return 0.1;
    return exp(-x*x/(2*sigma*sigma))/(sigma*sqrt(2*M_PI));
}

double uniform(double x){
    double L1=0;
    double L2=10;
    if (x<-1000) return 1;
    if(x>L1&&x<L2) return 1/(L2-L1);
    return 0;
}

double maxwellian2(double x){
    double temp=0.1;
    double sigma=sqrt(temp);
    if (x<-1000) return 2.1;
    return exp(-(x-2)*(x-2)/(2*sigma*sigma))/(sigma*sqrt(2*M_PI));
}

double maxwellian02(double x){
    double temp=0.1;
    double sigma=sqrt(temp);
    if (x<-1000) return -1.9;
    return exp(-(x+2)*(x+2)/(2*sigma*sigma))/(sigma*sqrt(2*M_PI));
}

double uniformE(double x){
    double L1=0;
    double L2=5;
    if (x<-1000) return 1;
    if(x>L1&&x<L2) return 1/(L2-L1);
    return 0;
}

double uniformP(double x){
    double L1=5;
    double L2=10;
    if (x<-1000) return 6;
    if(x>L1&&x<L2) return 1/(L2-L1);
    return 0;
}

int main(){

    int n_particles[2];
    n_particles[0] = 10;
    n_particles[1] = 10;
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
    sim simulation(10, 1, 0.1, 1, 1e-3, 2, n_particles, ctm, f, 1, fields);
    cout << "running simulation" << endl;
    simulation.run(1, 0.03);
    cout << "simulation complete" << endl;
}