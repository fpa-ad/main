#ifndef __FIELD__
#define __FIELD__

using namespace std;

class Field{
    public:

    Field(double fLx, double fLy, double fhx, double fhy);
    ~Field();

    double Xderiv(int nx, int ny);
    double Yderiv(int nx, int ny);
    double X2deriv(int nx, int ny);
    double Y2deriv(int nx, int ny);

    void Update(double** rho);
    
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
