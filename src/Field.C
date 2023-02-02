#include "Field.h"

Field::Field(double fLx, double fLy, double fhx, double fhy, double fext_x, double fext_y, double fext_z){
    Lx=fLx;
    Nx=(int)(fLx/fhx);
    hx=fLx/((double)(Nx));
    Ly=fLy;
    Ny=(int)(fLy/fhy);
    hy=fLy/((double)(Ny));
    
    //Create Edge points
    Nx++;
    Ny++;

    phi=new double*[Nx];
    for(int i=0; i<Nx; ++i){
        phi[i]=new double[Ny];
        for(int j=0; j<Ny; ++j){
            phi[i][j]=0;
        }
    }

    Fx=new double*[Nx];
    for(int i=0; i<Nx; ++i){
        Fx[i]=new double[Ny];
        for(int j=0; j<Ny; ++j){
            Fx[i][j]=0;
        }
    }

    Fy=new double*[Nx];
    for(int i=0; i<Nx; ++i){
        Fy[i]=new double[Ny];
        for(int j=0; j<Ny; ++j){
            Fy[i][j]=0;
        }
    }

    Fz=new double*[Nx];
    for(int i=0; i<Nx; ++i){
        Fz[i]=new double[Ny];
        for(int j=0; j<Ny; ++j){
            Fz[i][j]=0;
        }
    }

    ext_x=fext_x;
    ext_y=fext_y;
    ext_z=fext_z;
}

Field::~Field(){
    for(int i=0; i<Nx;++i){
        delete [] phi[i];
        delete [] Fx[i];
        delete [] Fy[i];
    }
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

double Field::get_X(double x, double y){
    int auxX = (int)(x/hx);
    int auxY = (int)(y/hy);
    if(auxX<Nx&&auxY<Ny)
        return Fx[auxX][auxY]+ext_x;
    return ext_x;
}

double Field::get_Y(double x, double y){
    int auxX = (int)(x/hx);
    int auxY = (int)(y/hy);
    if(auxX<Nx&&auxY<Ny)
        return Fy[auxX][auxY]+ext_y;
    return ext_y;
}

void Field::Update(int n_types, int* n_particles, double* ctm, particle** particles){
    
    /*double** rho=new double*[Nx];
    for (int i=0;i<Nx;i++){
        //rho[i]=(double*) malloc(Ny*sizeof(double));
        rho[i]=new double[Ny];
        for(int j=0; j<Ny; j++){
            rho[i][j]=0;
        }
    }

    //Density(n_types,n_particles,ctm,particles,rho);
    
    for(int i=0;i<Nx;i++){
        free(rho[i]);
    }
    free(rho);*/

    /*double** testvec = new double*[Nx];
    for (int i=0;i<Nx;i++){
        testvec[i] = new double[Ny];
    }
    for(int i=0;i<Nx;i++){
        delete [] testvec[i];
    }
    delete [] testvec;*/

}

void Field::Density(int n_types, int* n_particles, double* ctm, particle** particles, double** rho){
    
    for (int i=0;i<n_types;++i){
        for(int j=0; j<n_particles[i]; ++j){
            rho[(int)(particles[i][j].get_x()/hx)][(int)(particles[i][j].get_y()/hy)]+=ctm[i]/(hx*hy);
        }
    }
    
}