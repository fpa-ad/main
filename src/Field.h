#ifndef __FIELD__
#define __FIELD__

#include "particle.h"
#include <cmath>
#include "myutils.h"
#include <iostream>

using namespace std;

class Field{
    public:

    // Constructor
    Field();
    // Constructor
    //@param fLx x length of the box
    //@param fLy y length of the box
    //@param fhx x grid size
    //@param fhy y grid size
    //@param fext_x external field, x direction
    //@param fext_y external field, y direction
    //@param fext_z external field, z direction
    Field(double fLx, double fLy, double fhx, double fhy, double fext_x, double fext_y, double fext_z);
    // Constructor
    //@param F1 field object
    Field(const Field& F1);

    // Destructor
    /*~Field()*/

    // X derivative
    //@param nx x grid coordinate
    //@param ny y grid coordinate
    double Xderiv(int nx, int ny);
    // Y derivative
    //@param nx x grid coordinate
    //@param ny y grid coordinate
    double Yderiv(int nx, int ny);
    // Second X derivative
    //@param nx x grid coordinate
    //@param ny y grid coordinate
    double X2deriv(int nx, int ny);
    // Second Y derivative
    //@param nx x grid coordinate
    //@param ny y grid coordinate
    double Y2deriv(int nx, int ny);

    // Return field in the X direction
    //@param x x position
    //@param y y position
    double get_X(double x, double y);
    // Return field in the Y direction
    //@param x x position
    //@param y y position
    double get_Y(double x, double y);
    // Return field in the Z direction
    //@param x x position
    //@param y y position
    double get_Z(double x, double y);
    // Return internal phi field
    //@param i x grid coordinate
    //@param j y grid coordinate
    double get_phi(int i, int j);

    // Function to calculate the field, given the charge density
    //@param n_types number of particle types
    //@param n_particles array with number of particles of each type (size n)
    //@param ctm array with charge to mass ratios for the particle types (size n)
    //@param particles particle matrix
    void Update(int n_types, int* n_particles, double* ctm, particle** particles);

    void Poisson(double** rho);

    // Function to calculate density given the particle positions
    //@param n_types number of particle types
    //@param n_particles array with number of particles of each type (size n)
    //@param ctm array with charge to mass ratios for the particle types (size n)
    //@param particles particle matrix
    //@param rho ??
    void Density(int n_types, int* n_particles, double* ctm, particle** particles, double** rho);

    // ??
    //@param p ??
    //@param q ??
    //@param m ??
    //@param n ??
    //@param A ??
    //@param B ??
    //@param R ??
    void Kronecker(int p, int q, int m, int n, double** A, double** B, double** R);

    // LU matrix decomposition
    //@param A matrix to decompose
    //@param L L matrix for the result
    //@param U U matrix for the result
    //@param N size of the matrix (NxN)
    void LUdecomp(double** A, double** L, double** U, int N);

    // LU matrix inversion
    //@param A original matrix, where the inverse is put
    //@param L lower triangular matrix
    //@param U upper triangular matrix
    //@param N size of the matrices (NxX)
    void LUinverse(double** A, double** L, double** U, int N);

    // Initialization of the MatFD matrix
    void InitializeMatFD();
    
    private:
        // Size of box - x direction
        double Lx=0;
        // Grid size - x direction
        double hx=0;
        // Number of grid points - x direction
        int Nx=0;
        // Size of box - y direction
        double Ly=0;
        // Grid size - y direction
        double hy=0;
        // Number of grid points - y direction
        int Ny=0;
        // Internal phi field
        double** phi=nullptr;
        // ??
        double** Fx=nullptr;
        // ??
        double** Fy=nullptr;
        // ??
        double** Fz=nullptr;
        // External field - x direction
        double ext_x=0;
        // External field - y direction
        double ext_y=0;
        // External field - z direction
        double ext_z=0;
        //Matrices for solving
        double** Mat;
};
#endif
