#include "Field.h"

Field::Field(){
    Lx=0;
    Ly=0;
    Nx=0;
    Ny=0;
    hx=0;
    hy=0;
    ext_x=0;
    ext_y=0;
    ext_z=0;
    phi=nullptr;
    Fx=nullptr;
    Fy=nullptr;
    Fz=nullptr;
}

Field::Field(double fLx, double fLy, double fhx, double fhy, double fext_x, double fext_y, double fext_z){
    Lx=fLx;
    Nx=(int)(fLx/fhx);
    hx=fLx/((double)(Nx));
    Ly=fLy;
    Ny=(int)(fLy/fhy);
    hy=fLy/((double)(Ny));
    
    //Create Edge points
    //Nx++;
    //Ny++;

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

Field::Field(const Field& F1){
    Lx=F1.Lx;
    Nx=F1.Lx;
    hx=F1.hx;
    Ly=F1.Ly;
    Ny=F1.Ny;
    hy=F1.hy;

    phi=new double*[Nx];
    for(int i=0; i<Nx; ++i){
        phi[i]=new double[Ny];
        for(int j=0; j<Ny; ++j){
            phi[i][j]=F1.phi[i][j];
        }
    }

    Fx=new double*[Nx];
    for(int i=0; i<Nx; ++i){
        Fx[i]=new double[Ny];
        for(int j=0; j<Ny; ++j){
            Fx[i][j]=F1.Fx[i][j];
        }
    }

    Fy=new double*[Nx];
    for(int i=0; i<Nx; ++i){
        Fy[i]=new double[Ny];
        for(int j=0; j<Ny; ++j){
            Fy[i][j]=F1.Fy[i][j];
        }
    }

    Fz=new double*[Nx];
    for(int i=0; i<Nx; ++i){
        Fz[i]=new double[Ny];
        for(int j=0; j<Ny; ++j){
            Fz[i][j]=F1.Fz[i][j];
        }
    }

    ext_x=F1.ext_x;
    ext_y=F1.ext_y;
    ext_z=F1.ext_z;
}

/*Field::~Field(){
    cout<<"Field destructor called"<<endl;
    for(int i=0; i<Nx;++i){
        delete [] phi[i];
        delete [] Fx[i];
        delete [] Fy[i];
    }
    delete [] phi;
    delete [] Fx;
    delete [] Fy;
}*/

double Field::Xderiv(int nx, int ny){
    if(nx==0 || nx==Nx-1)
        return ((phi[1][ny]-phi[Nx-2][ny])/(2*hx));
    return ((phi[nx+1][ny]-phi[nx-1][ny])/(2*hx));
}
    
double Field::Yderiv(int nx, int ny){
    if(ny==0)
        return ((phi[nx][1]-phi[nx][Ny-1])/(2*hy));
    if(ny==Ny-1)
        return ((phi[nx][0]-phi[nx][Ny-2])/(2*hy));
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
    if(auxX==Nx) auxX=0;
    if(auxY==Ny) auxY=0;


    if(auxX>=0 && auxX<Nx && auxY>=0 && auxY<Ny)
        return Fx[auxX][auxY]+ext_x;
    
    return ext_x;
}

double Field::get_Y(double x, double y){
    int auxX = (int)(x/hx);
    int auxY = (int)(y/hy);
    if(auxX==Nx) auxX=0;
    if(auxY==Ny) auxY=0;


    if(auxX>=0 && auxX<Nx && auxY>=0 && auxY<Ny)
        return Fy[auxX][auxY]+ext_y;
    
    return ext_y;
}

double Field::get_Z(double x, double y){
    int auxX = (int)(x/hx);
    int auxY = (int)(y/hy);
    if(auxX==Nx) auxX=0;
    if(auxY==Ny) auxY=0;


    if(auxX>=0 && auxX<Nx && auxY>=0 && auxY<Ny)
        return Fz[auxX][auxY]+ext_z;
    
    return ext_z;
}

void Field::Update(int n_types, int* n_particles, double* ctm, particle** particles){
    
    double** rho=new double*[Nx];
    for (int i=0;i<Nx;i++){
        rho[i]=new double[Ny];
        for(int j=0; j<Ny; j++){
            rho[i][j]=0;
        }
    }

    Density(n_types,n_particles,ctm,particles,rho);

    /////////////

    /////////////
    
    for(int i=0;i<Nx;i++){
        delete [] rho[i];
    }
    delete [] rho;
}

void Field::Density(int n_types, int* n_particles, double* ctm, particle** particles, double** rho){

    for (int i=0;i<n_types;++i){
        for(int j=0; j<n_particles[i]; ++j){
            int auxX = (int)(particles[i][j].get_x()/hx);
            int auxY = (int)(particles[i][j].get_y()/hy);
            if(auxX==Nx) auxX=0;
            if(auxY==Ny) auxY=0;

            rho[auxX][auxY]+=ctm[i]/(hx*hy);
        }
    }
    
}