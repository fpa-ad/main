#include "Field.h"

Field::Field() : Lx(0), Ly(0), Nx(0), Ny(0), hx(0), hy(0), ext_x(0), ext_y(0), ext_z(0), phi(nullptr), Fx(nullptr), Fy(nullptr), Fz(nullptr) {
    Mat=new double*[Nx*Ny];
    for(int i=0; i<Nx*Ny; ++i){
        Mat[i]=new double[Nx*Ny];
        for(int j=0; j<Nx*Ny; ++j){
            Mat[i][j]=0;
        }
    }
    InitializeMatFD();
}

Field::Field(double fLx, double fLy, double fhx, double fhy, double fext_x, double fext_y, double fext_z) : Lx(fLx), Ly(fLy), ext_x(fext_x), ext_y(fext_y), ext_z(fext_z) {
    Nx=(int)(fLx/fhx);
    hx=fLx/((double)(Nx));
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

    Mat=new double*[Nx*Ny];
    for(int i=0; i<Nx*Ny; ++i){
        Mat[i]=new double[Nx*Ny];
        for(int j=0; j<Nx*Ny; ++j){
            Mat[i][j]=0;
        }
    }
    InitializeMatFD();

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

    Mat=new double*[Nx*Ny];
    for(int i=0; i<Nx*Ny; ++i){
        Mat[i]=new double[Nx*Ny];
        for(int j=0; j<Nx*Ny; ++j){
            Mat[i][j]=0;
        }
    }
    InitializeMatFD();
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
    int nxplus=nx+1;
    int nxminus=nx-1;
    if(nxminus==-1) nxminus=Nx-1;
    if(nxplus==Nx) nxplus=0;
    return ((phi[nxplus][ny]-phi[nxminus][ny])/(2*hx));
}
    
double Field::Yderiv(int nx, int ny){
    int nyplus=ny+1;
    int nyminus=ny-1;
    if(nyminus==-1) nyminus=Ny-1;
    if(nyplus==Ny) nyplus=0;
    return ((phi[nx][nyplus]-phi[nx][nyminus])/(2*hy));
}
    
double Field::X2deriv(int nx, int ny){
    int nxplus=nx+1;
    int nxminus=nx-1;
    if(nxminus==-1) nxminus=Nx-1;
    if(nxplus==Nx) nxplus=0;
    return ((phi[nxplus][ny]-2*phi[nx][ny]+phi[nxminus][ny])/(hx*hx));
}

double Field::Y2deriv(int nx, int ny){
    int nyplus=ny+1;
    int nyminus=ny-1;
    if(nyminus==-1) nyminus=Ny-1;
    if(nyplus==Ny) nyplus=0;
    return ((phi[nx][nyplus]-2*phi[nx][ny]+phi[nx][nyminus])/(hy*hy));
}

double Field::get_phi(int i, int j){
    return phi[i][j];
}

double Field::get_X(double x, double y){
    double res=0;

    for(int i=0; i<Nx; ++i){
        for(int j=0; j<Ny; ++j){
            res+=hx*hy*Fx[i][j]*(Spline1(x-i*hx,hy)+Spline1(x-Lx-i*hx,hy)+Spline1(x+Lx-i*hx,hy))*(Spline1(y-j*hy,hy)+Spline1(y-Ly-j*hy,hy)+Spline1(y+Ly-j*hy,hy));
        }
    }
    
    return res+ext_x;
}

double Field::get_Y(double x, double y){
    double res=0;

    for(int i=0; i<Nx; ++i){
        for(int j=0; j<Ny; ++j){
            res+=hx*hy*Fy[i][j]*(Spline1(x-i*hx,hy)+Spline1(x-Lx-i*hx,hy)+Spline1(x+Lx-i*hx,hy))*(Spline1(y-j*hy,hy)+Spline1(y-Ly-j*hy,hy)+Spline1(y+Ly-j*hy,hy));
        }
    }
    
    return res+ext_y;
}

double Field::get_Z(double x, double y){
    double res=0;

    for(int i=0; i<Nx; ++i){
        for(int j=0; j<Ny; ++j){
            res+=hx*hy*Fz[i][j]*(Spline1(x-i*hx,hy)+Spline1(x-Lx-i*hx,hy)+Spline1(x+Lx-i*hx,hy))*(Spline1(y-j*hy,hy)+Spline1(y-Ly-j*hy,hy)+Spline1(y+Ly-j*hy,hy));
        }
    }
    
    return res+ext_z;
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

    Poisson(rho);
    
    for(int i=0;i<Nx;i++){
        delete [] rho[i];
    }
    delete [] rho;
}

void Field::Density(int n_types, int* n_particles, double* ctm, particle** particles, double** rho){
    int superparticle_N=1;
    for(int i=0; i<Nx; ++i){
        for (int j=0; j<Ny;++j){
            for (int p_type=0;p_type<n_types;++p_type){
                for(int p=0; p<n_particles[p_type]; ++p){
                    rho[i][j]+=superparticle_N*ctm[p_type]*(Spline1(i*hx-particles[p_type][p].get_x(),hx)+Spline1(i*hx+Lx-particles[p_type][p].get_x(),hx)+Spline1(i*hx-Lx-particles[p_type][p].get_x(),hx))*(Spline1(j*hy-particles[p_type][p].get_y(),hy)+Spline1(j*hy+Ly-particles[p_type][p].get_y(),hy)+Spline1(j*hy-Ly-particles[p_type][p].get_y(),hy));
                }
            }
        }
    }
    
}

void Field::Poisson(double** rho){
    
    double* R = new double[Nx*Ny];
    for(int i = 0; i<Nx; ++i){
        for(int j = 0; j<Ny; ++j){
            R[i*Ny+j]=-rho[i][j];
        }
    }
    R[Nx*Ny-1]=0;

    double* vecphi = new double[Nx*Ny];
    for(int i = 0; i<Nx; ++i){
        for(int j = 0; j<Ny; ++j){
            vecphi[i*Ny+j]=0;
        }
    }

    ////vecphi=Mat.R
    for(int i=0; i<Nx*Ny; ++i){
        for(int j=0; j<Nx*Ny; ++j){
            vecphi[i]+=R[j]*Mat[i][j];
        }    
    }

    ///Put it all in phi Fx Fy
    for(int i = 0; i<Nx; ++i){
        for(int j = 0; j<Ny; ++j){
            phi[i][j]=vecphi[i*Ny+j];
        }
    }

    for(int i = 0; i<Nx; ++i){
        for(int j = 0; j<Ny; ++j){
            Fx[i][j]=-Xderiv(i,j);
        }
    }

    for(int i = 0; i<Nx; ++i){
        for(int j = 0; j<Ny; ++j){
            Fy[i][j]=-Yderiv(i,j);
        }
    }

    //Free all the memory

    delete [] R;
    delete [] vecphi;

}

void Field::InitializeMatFD(){

    double** Ax=new double*[Ny];
    for(int i=0; i<Ny; ++i){
        Ax[i]=new double[Ny];
        for(int j=0; j<Ny; ++j){
            Ax[i][j]=0;
            if(j==i) Ax[i][j]+=-2;
            if(j==i+1||j==i-1) Ax[i][j]+=1;
            if(j==0&&i==Nx-1)Ax[i][j]+=1;
            if(j==Nx-1&&i==0) Ax[i][j]+=1;
        }
    }

    double** Ay=new double*[Nx];
    for(int i=0; i<Nx; ++i){
        Ay[i]=new double[Nx];
        for(int j=0; j<Nx; ++j){
            Ay[i][j]=0;
            if(j==i) Ay[i][j]+=-2;
            if(j==i+1||j==i-1) Ay[i][j]+=1;
            if(j==0&&i==Nx-1)Ay[i][j]+=1;
            if(j==Nx-1&&i==0) Ay[i][j]+=1;
        }
    }

    double** Iy=new double*[Ny];
    for(int i=0; i<Ny; ++i){
        Iy[i]=new double[Ny];
        for(int j=0; j<Ny; ++j){
            Iy[i][j]=0;
            if(j==i) Iy[i][j]=1;
        }
    }

    double** Ix=new double*[Nx];
    for(int i=0; i<Nx; ++i){
        Ix[i]=new double[Nx];
        for(int j=0; j<Nx; ++j){
            Ix[i][j]=0;
            if(j==i) Ix[i][j]=1;
        }
    }

    double** Matx=new double*[Nx*Ny];
    for(int i=0; i<Nx*Ny; ++i){
        Matx[i]=new double[Nx*Ny];
        for(int j=0; j<Nx*Ny; ++j){
            Matx[i][j]=0;
        }
    }
    double** Maty=new double*[Nx*Ny];
    for(int i=0; i<Nx*Ny; ++i){
        Maty[i]=new double[Nx*Ny];
        for(int j=0; j<Nx*Ny; ++j){
            Maty[i][j]=0;
        }
    }

    Kronecker(Ny,Ny,Nx,Nx,Ax,Ix,Matx);
    Kronecker(Ny,Ny,Nx,Nx,Iy,Ay,Maty);

    for(int i=0; i<Nx*Ny-1; ++i){
        for(int j=0; j<Nx*Ny; ++j){
            Mat[i][j]=Matx[i][j]+Maty[i][j];
        }
    }
    for(int j=0; j<Nx*Ny; ++j){
        Mat[Nx*Ny-1][j]=1;
    }

    double** LMat=new double*[Nx*Ny];
    for(int i=0; i<Nx*Ny; ++i){
        LMat[i]=new double[Nx*Ny];
        for(int j=0; j<Nx*Ny; ++j){
            LMat[i][j]=0;
        }
    }
    double** UMat=new double*[Nx*Ny];
    for(int i=0; i<Nx*Ny; ++i){
        UMat[i]=new double[Nx*Ny];
        for(int j=0; j<Nx*Ny; ++j){
            UMat[i][j]=0;
        }
    }
    cout<<"Finite Differences Setup Start"<<endl;
    LUdecomp(Mat,LMat,UMat,Nx*Ny);
    LUinverse(Mat,LMat,UMat,Nx*Ny);

    //Free all the memory

    for(int i = 0; i<Nx; ++i){
        delete [] Ay[i];
        delete [] Ix[i];
    }
    for(int i = 0; i<Ny; ++i){
        delete [] Ax[i];
        delete [] Iy[i];
    }
    for(int i = 0; i<Nx*Ny; ++i){
        delete [] Matx[i];
        delete [] Maty[i];
        delete [] LMat[i];
        delete [] UMat[i];
    }
    delete [] Ax;
    delete [] Ay;
    delete [] Ix;
    delete [] Iy;
    delete [] Matx;
    delete [] Maty;
    delete [] LMat;
    delete [] UMat;
}

void Field::Kronecker(int p, int q, int m, int n, double** A, double** B, double** R){
    for(int i=0; i<p*m; ++i){
        for(int j=0; j<q*n; ++j){
            R[i][j]=A[i/m][j/n]*B[i%m][j%n];
        }
    }
}

void Field::LUdecomp(double** A, double** L, double** U, int N){

    for (int i = 0; i<N; ++i){
        for (int j=0; j<N; ++j){
            L[i][j]=0;
            U[i][j]=0;
            if (i==j) L[i][j]=1;
        }
    }

    //setup of L and U matrices ^^^^^^^

    for (int i = 0; i<N;++i){
        for(int j = i; j<N; ++j){
            U[i][j]=A[i][j];
            for(int k = 0; k<i; ++k){
                U[i][j]=U[i][j]-L[i][k]*U[k][j];
            }
        }
        for(int j = i+1; j<N; ++j){
            L[j][i]=A[j][i];
            for(int k = 0; k<i; ++k){
                L[j][i]=L[j][i]-L[j][k]*U[k][i];
            }
            L[j][i]=L[j][i]/U[i][i];
        }
        cout<<"LU Decomposition "<<(((double)(i))/N*100)<<"\% Complete!\r"<<flush;
    }
    cout<<endl;
}

void Field::LUinverse(double** A, double** L, double** U, int N){
    
    for(int i=0; i<N; ++i){ //loop for each collumn of the inverse matrix (Bcol)
        double* Bcol=new double[N];
        double* Icol=new double[N];
        double* Zcol=new double[N];
        for(int j=0; j<N; ++j){ //loop to fill Icol
            Icol[j]=0;
            Bcol[j]=0;
            Zcol[j]=0;
            if(j==i) Icol[j]=1;
        }
        //Solve single Linear system
        //Solve L.Zcol=Icol
        for(int j=0; j<N; ++j){
            double aux=0;
            for(int k=0; k<j; ++k){
                aux+=L[j][k]*Zcol[k];
            }
            Zcol[j]=Icol[j]-aux;
        }
        //Solve U.Bcol=Zcol
        for(int j=N-1; j>=0; --j){
            double aux2=0;
            for(int k=j+1; k<N; ++k){
                aux2+=U[j][k]*Bcol[k];
            }
            Bcol[j]=(Zcol[j]-aux2)/U[j][j];
        }
        // Put Bcol in A
        for(int j=0; j<N; ++j){
            A[j][i]=Bcol[j];
        }
        cout<<"Inverting "<<(((double)(i))/N*100)<<"\% Complete!\r"<<flush;
    }
    cout<<endl;
}