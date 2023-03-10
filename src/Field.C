#include "Field.h"

// Constructor
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

// Constructor
//@param fLx x length of the box
//@param fLy y length of the box
//@param fhx x grid size
//@param fhy y grid size
//@param fext_x external field, x direction
//@param fext_y external field, y direction
//@param fext_z external field, z direction
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

// Constructor
//@param F1 field object
Field::Field(const Field& F1): Lx(F1.Lx), Nx(F1.Nx), hx(F1.hx), Ly(F1.Ly), Ny(F1.Ny), hy(F1.hy) {
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
        delete [] Fz[i];
    }
    delete [] phi;
    delete [] Fx;
    delete [] Fy;
    delete [] Fz;
}*/

// X derivative
//@param nx x grid coordinate
//@param ny y grid coordinate
double Field::Xderiv(int nx, int ny){
    int nxplus=nx+1;
    int nxminus=nx-1;
    if(nxminus==-1) nxminus=Nx-1;
    if(nxplus==Nx) nxplus=0;
    return ((phi[nxplus][ny]-phi[nxminus][ny])/(2*hx));
}

// Y derivative
//@param nx x grid coordinate
//@param ny y grid coordinate
double Field::Yderiv(int nx, int ny){
    int nyplus=ny+1;
    int nyminus=ny-1;
    if(nyminus==-1) nyminus=Ny-1;
    if(nyplus==Ny) nyplus=0;
    return ((phi[nx][nyplus]-phi[nx][nyminus])/(2*hy));
}

// Second X derivative
//@param nx x grid coordinate
//@param ny y grid coordinate
double Field::X2deriv(int nx, int ny){
    int nxplus=nx+1;
    int nxminus=nx-1;
    if(nxminus==-1) nxminus=Nx-1;
    if(nxplus==Nx) nxplus=0;
    return ((phi[nxplus][ny]-2*phi[nx][ny]+phi[nxminus][ny])/(hx*hx));
}

// Second Y derivative
//@param nx x grid coordinate
//@param ny y grid coordinate
double Field::Y2deriv(int nx, int ny){
    int nyplus=ny+1;
    int nyminus=ny-1;
    if(nyminus==-1) nyminus=Ny-1;
    if(nyplus==Ny) nyplus=0;
    return ((phi[nx][nyplus]-2*phi[nx][ny]+phi[nx][nyminus])/(hy*hy));
}

// Return field in the X direction
//@param x x position
//@param y y position
double Field::get_X(double x, double y){
    double res=0;

    for(int i=0; i<Nx; ++i){
        for(int j=0; j<Ny; ++j){
            res+=hx*hy*Fx[i][j]*(Spline1(x-i*hx,hy)+Spline1(x-Lx-i*hx,hy)+Spline1(x+Lx-i*hx,hy))*(Spline1(y-j*hy,hy)+Spline1(y-Ly-j*hy,hy)+Spline1(y+Ly-j*hy,hy));
        }
    }
    
    return res+ext_x;
}

// Return field in the Y direction
//@param x x position
//@param y y position
double Field::get_Y(double x, double y){
    double res=0;

    for(int i=0; i<Nx; ++i){
        for(int j=0; j<Ny; ++j){
            res+=hx*hy*Fy[i][j]*(Spline1(x-i*hx,hy)+Spline1(x-Lx-i*hx,hy)+Spline1(x+Lx-i*hx,hy))*(Spline1(y-j*hy,hy)+Spline1(y-Ly-j*hy,hy)+Spline1(y+Ly-j*hy,hy));
        }
    }
    
    return res+ext_y;
}

// Return field in the Z direction
//@param x x position
//@param y y position
double Field::get_Z(double x, double y){
    double res=0;

    for(int i=0; i<Nx; ++i){
        for(int j=0; j<Ny; ++j){
            res+=hx*hy*Fz[i][j]*(Spline1(x-i*hx,hy)+Spline1(x-Lx-i*hx,hy)+Spline1(x+Lx-i*hx,hy))*(Spline1(y-j*hy,hy)+Spline1(y-Ly-j*hy,hy)+Spline1(y+Ly-j*hy,hy));
        }
    }
    
    return res+ext_z;
}

// Return internal phi field
//@param i x grid coordinate
//@param j y grid coordinate
double Field::get_phi(int i, int j){
    return phi[i][j];
}

// Function to calculate the field, given the charge density
//@param n_types number of particle types
//@param n_particles array with number of particles of each type (size n)
//@param ctm array with charge to mass ratios for the particle types (size n)
//@param particles particle matrix
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

// Function to update the internal field
//@param rho density matrix at gridpoints (from Density)
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

// Function to calculate density given the particle positions
//@param n_types number of particle types
//@param n_particles array with number of particles of each type (size n)
//@param ctm array with charge to mass ratios for the particle types (size n)
//@param particles particle matrix
//@param rho density matrix at the grid points, onto which the result will be copied
void Field::Density(int n_types, int* n_particles, double* ctm, particle** particles, double** rho){
    double quasi=0;

    for(int i=0; i<n_types; ++i){
        quasi -= ctm[i];
    }

    //cout<<"quasi= "<<quasi<<endl;

    int Npart=0;
    Npart+=n_particles[0];

    for(int i=0; i<Nx; ++i){
        for (int j=0; j<Ny;++j){
            for (int p_type=0;p_type<n_types;++p_type){
                for(int p=0; p<n_particles[p_type]; ++p){
                    rho[i][j]+=Lx*Ly/Npart*ctm[p_type]*(Spline1(i*hx-particles[p_type][p].get_x(),hx)+Spline1(i*hx+Lx-particles[p_type][p].get_x(),hx)+Spline1(i*hx-Lx-particles[p_type][p].get_x(),hx))*(Spline1(j*hy-particles[p_type][p].get_y(),hy)+Spline1(j*hy+Ly-particles[p_type][p].get_y(),hy)+Spline1(j*hy-Ly-particles[p_type][p].get_y(),hy));
                }
            }
            rho[i][j]+=quasi;
        }
    }
    
}

// Function to calculate the kronecker (tensor) product of two matrices
//@param p number of lines of matrix A
//@param q number of columns of matrix A
//@param m number of lines of matrix B
//@param n number of columns of matrix B
//@param A First matrix to multiply
//@param B Second matrix to multiply
//@param R Matrix onto which the result will be copied (must be (p*m)x(q*n))
void Field::Kronecker(int p, int q, int m, int n, double** A, double** B, double** R){
    for(int i=0; i<p*m; ++i){
        for(int j=0; j<q*n; ++j){
            R[i][j]=A[i/m][j/n]*B[i%m][j%n];
        }
    }
}

// LU matrix decomposition
//@param A matrix to decompose
//@param L L matrix for the result
//@param U U matrix for the result
//@param N size of the matrix (NxN)
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

// LU matrix inversion
//@param A original matrix, where the inverse is put
//@param L lower triangular matrix
//@param U upper triangular matrix
//@param N size of the matrices (NxX)
void Field::LUinverse(double** A, double** L, double** U, int N){
    
    for(int i=0; i<N; ++i){ //loop for each column of the inverse matrix (Bcol)
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

// Initialization of the MatFD matrix
void Field::InitializeMatFD(){

    double** Ay=new double*[Ny];
    for(int i=0; i<Ny; ++i){
        Ay[i]=new double[Ny];
        for(int j=0; j<Ny; ++j){
            Ay[i][j]=0;
            if(j==i) Ay[i][j]+=-2;
            if(j==i+1||j==i-1) Ay[i][j]+=1;
            if(j==0&&i==Ny-1)Ay[i][j]+=1;
            if(j==Ny-1&&i==0) Ay[i][j]+=1;
            Ay[i][j]/=(hy*hy);
        }
    }

    double** Ax=new double*[Nx];
    for(int i=0; i<Nx; ++i){
        Ax[i]=new double[Nx];
        for(int j=0; j<Nx; ++j){
            Ax[i][j]=0;
            if(j==i) Ax[i][j]+=-2;
            if(j==i+1||j==i-1) Ax[i][j]+=1;
            if(j==0&&i==Nx-1)Ax[i][j]+=1;
            if(j==Nx-1&&i==0) Ax[i][j]+=1;
            Ax[i][j]/=(hx*hx);
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

    Kronecker(Ny,Ny,Nx,Nx,Ay,Ix,Matx);
    Kronecker(Ny,Ny,Nx,Nx,Iy,Ax,Maty);

    for(int i=0; i<Nx*Ny-1; ++i){
        for(int j=0; j<Nx*Ny; ++j){
            Mat[i][j]=Matx[i][j]+Maty[i][j];
            //cout<<Mat[i][j]<<" ";
        }
        //cout<<endl;
    }
    //cout<<endl<<endl;

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
        delete [] Ax[i];
        delete [] Ix[i];
    }
    for(int i = 0; i<Ny; ++i){
        delete [] Ay[i];
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