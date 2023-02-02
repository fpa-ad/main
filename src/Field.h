#ifndef __FIELD__
#define __FIELD__

#include "particle.h"
#include <iostream>

using namespace std;

class Field{
    public:

    //Constructor
    Field(double fLx, double fLy, double fhx, double fhy, double fext_x, double fext_y, double fext_z);
    //Destructor
    ~Field();

    //Functions that calculate derivatives
    double Xderiv(int nx, int ny);
    double Yderiv(int nx, int ny);
    double X2deriv(int nx, int ny);
    double Y2deriv(int nx, int ny);

    //Get Fields
    double get_X(double x, double y);
    double get_Y(double x, double y);

    //Function to calculate the field, given the charge density
    void Update(int n_types, int* n_particles, double* ctm, particle** particles);
    //Function to calculate density given the particle positions
    void Density(int n_types, int* n_particles, double* ctm, particle** particles, double** rho);
    
    private:
    double Lx;
    double hx;
    int Nx;
    double Ly;
    double hy;
    int Ny;
    double** phi;
    double** Fx;
    double** Fy;
    double** Fz;
    double ext_x;
    double ext_y;
    double ext_z;
};
#endif
