#ifndef __FIELD__
#define __FIELD__

#include "particle.h"
#include <cmath>
#include "myutils.h"
#include <iostream>

using namespace std;

class Field{
    public:

    //Constructor
    Field();
    Field(double fLx, double fLy, double fhx, double fhy, double fext_x, double fext_y, double fext_z);
    Field(const Field& F1);
    //Destructor
    //~Field();

    //Functions that calculate derivatives
    double Xderiv(int nx, int ny);
    double Yderiv(int nx, int ny);
    double X2deriv(int nx, int ny);
    double Y2deriv(int nx, int ny);

    //Get Fields
    double get_X(double x, double y);
    double get_Y(double x, double y);
    double get_Z(double x, double y);

    //Function to calculate the field, given the charge density
    void Update(int n_types, int* n_particles, double* ctm, particle** particles);
    void Poisson(double** rho);
    //Function to calculate density given the particle positions
    void Density(int n_types, int* n_particles, double* ctm, particle** particles, double** rho);

    void Kronecker(int p, int q, int m, int n, double** A, double** B, double** R);
    void LUdecomp(double** A, double** L, double** U, int N);
    void LUinverse(double** A, double** L, double** U, int N);
    void InitializeMatFD();
    
    private:
    double Lx=0;
    double hx=0;
    int Nx=0;
    double Ly=0;
    double hy=0;
    int Ny=0;
    double** phi=nullptr;
    double** Fx=nullptr;
    double** Fy=nullptr;
    double** Fz=nullptr;
    double ext_x=0;
    double ext_y=0;
    double ext_z=0;
    //Matrices for solving
    double** Mat;
};
#endif
