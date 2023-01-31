#include "Field.h"

Field::Field(double fLx, double fLy, double fhx, double fhy){
    Lx=fLx;
    Nx=(int)(fLx/fhx);
    hx=fLx/((double)(Nx));
    Ly=fLy;
    Ny=(int)(fLy/fhy);
    hy=fLy/((double)(Ny));

    phi=new double*[Nx];
    for(int i=0; i<Nx; ++i){
        phi[i]=new double[Ny];
    }

    Fx=new double*[Nx];
    for(int i=0; i<Nx; ++i){
        Fx[i]=new double[Ny];
    }

    Fy=new double*[Nx];
    for(int i=0; i<Nx; ++i){
        Fy[i]=new double[Ny];
    }
}


Field::~Field(){
    delete [] phi;
    delete [] Fx;
    delete [] Fy;
}

double Field::Xderiv(int nx, int ny){
    if(nx==0)
        return ((phi[nx+1][ny]-phi[nx][ny])/hx);
    if(nx==Nx-1)
        return ((phi[nx][ny]-phi[nx-1][ny])/hx);
    return ((phi[nx+1][ny]-phi[nx-1][ny])/(2*hx));
}
    
double Field::Yderiv(int nx, int ny){
    if(ny==0)
        return ((phi[nx][ny+1]-phi[nx][ny])/hy);
    if(ny==Ny-1)
        return ((phi[nx][ny]-phi[nx][ny-1])/hy);
    return ((phi[nx][ny+1]-phi[nx][ny-1])/(2*hy));
}
    
double Field::X2deriv(int nx, int ny){
    if(nx==0)
        return ((phi[nx+1][ny]-2*phi[nx][ny])/(hx*hx));
    if(nx==Nx-1)
        return ((-2*phi[nx][ny]+phi[nx-1][ny])/(hx*hx));
    return ((phi[nx+1][ny]-2*phi[nx][ny]+phi[nx-1][ny])/(hx*hx));
}

double Field::Y2deriv(int nx, int ny){
    if(ny==0)
        return ((phi[nx][ny+1]-2*phi[nx][ny])/(hy*hy));
    if(ny==Ny-1)
        return ((-2*phi[nx][ny]+phi[nx][ny-1])/(hy*hy));
    return ((phi[nx][ny+1]-2*phi[nx][ny]+phi[nx][ny-1])/(hy*hy));
}

void Field::Update(double** rho){
    ///Boi, this part is hard
}

double** Density(Field.update(int n_types, int* n_particles, double* ctm, particle** particles)){
    //Calculate rho
}

