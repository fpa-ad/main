#ifndef __FIELD__
#define __FIELD__

using namespace std;

class Field{
    public:

    //Constructor
    Field(double fLx, double fLy, double fhx, double fhy);
    //Destructor
    ~Field();

    //Functions that calculate derivatives
    double Xderiv(int nx, int ny);
    double Yderiv(int nx, int ny);
    double X2deriv(int nx, int ny);
    double Y2deriv(int nx, int ny);

    //Function to calculate the field, given the charge density
    void Update(double** rho);
    double** Density(Field.update(int n_types, int* n_particles, double* ctm, particle** particles));
    
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
};
#endif
