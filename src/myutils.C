#include "myutils.h"
#include <sstream>
#include <random>
#include <iostream>

using namespace std;

// Function to get current time; used to name folders
string current_time() {
    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);
    stringstream ss;
    ss << std::put_time(&tm, "%d-%m-%Y_%H-%M-%S");
    return ss.str();
}

// Function to get a Newton's method approximation of the solution to f(x)=a
//@param f function to apply Newton's method to
//@param a constant on the RHS of the equation f(x) = a
//@param x0 initial value for x
//@param iterations number of iterations of Newton's method
//@param h finite difference to calculate the derivative of the denominator of the method
double Newton(funcdouble f, double a, double x0, int iterations, double h){
    while(f(x0)<0.001){
        x0+=1;
    }
    for (int i=0; i<iterations; ++i){
        x0=x0-((f(x0)-a)*2*h)/(f(x0+h)-f(x0-h));
    }
    return x0;
}

// Function to get a Newton's method approximation of the solution to \int_{-\infty}^{x} f(t) dt = a (parameters optimized for position initialization)
//@param f function whose integral to apply Newton's method to
//@param a constant on the RHS of the equation f(x) = a
//@param x0 initial value for x
//@param iterations number of iterations of Newton's method
//@param h finite difference to calculate the derivative of the denominator of the method
double NewtonInt_X(funcdouble f, double a, double x0, int iterations, double h){
    for (int i=0; i<iterations; ++i){
        x0=x0-((Integral(f,0,x0,0.01)-a)*2*h)/(Integral(f, 0,x0+h,0.01)-Integral(f, 0,x0-h,0.01));
    }
    return x0;
}

// Function to get a Newton's method approximation of the solution to \int_{-\infty}^{x} f(t) dt = a (parameters optimized for low velocity initialization)
//@param f function whose integral to apply Newton's method to
//@param a constant on the RHS of the equation f(x) = a
//@param x0 initial value for x
//@param iterations number of iterations of Newton's method
//@param h finite difference to calculate the derivative of the denominator of the method
double NewtonInt_V(funcdouble f, double a, double x0, int iterations, double h){
    for (int i=0; i<iterations; ++i){
        x0=x0-((Integral(f,-1,x0,0.001)-a)*2*h)/(Integral(f,-1,x0+h,0.001)-Integral(f,-1,x0-h,0.001));
    }
    return x0;
}

// Function to get a Newton's method approximation of the solution to \int_{-\infty}^{x} f(t) dt = a (parameters optimized for high velocity initialization)
//@param f function whose integral to apply Newton's method to
//@param a constant on the RHS of the equation f(x) = a
//@param x0 initial value for x
//@param iterations number of iterations of Newton's method
//@param h finite difference to calculate the derivative of the denominator of the method
double NewtonInt_V2(funcdouble f, double a, double x0, int iterations, double h){
    for (int i=0; i<iterations; ++i){
        
        x0=x0-((Integral(f,-10,x0,0.01)-a)*2*h)/(Integral(f,-10,x0+h,0.01)-Integral(f,-10,x0-h,0.01));
    }
    return x0;
}

// Function to calculate the integral of f, over the interval [a,b]
//@param f function to calculate the integral of
//@param a beginning of interval
//@param a end of interval
//@param h spacing between sampled points
double Integral(funcdouble f, double a, double b, double h){
    double res=0;
    int iters=(int)((b-a)/h);
    h=(b-a)/iters;
    for (int i=0; i<iters; ++i){
        res+=f(a+i*h+h/2)*h;
    }
    return res;
}

// Function to calculate a random initial position
//@param f position distribution function
//@param rand random value between 0 and 1 to seed the random position
double InverseCDF_X(funcdouble f, double rand){
    double aux=f(-1001);
    return (NewtonInt_X(f,rand,aux,10,0.01));
}

// Function to calculate a random initial (low) velocity
//@param f velocity distribution function
//@param rand random value between 0 and 1 to seed the random velocity
double InverseCDF_V(funcdouble f, double rand){
    double aux=f(-1001);
    return (NewtonInt_V(f,rand,aux,10,0.001));
}

// Function to calculate a random initial (high) velocity
//@param f velocity distribution function
//@param rand random value between 0 and 1 to seed the random velocity
double InverseCDF_V2(funcdouble f, double rand){
    double aux=f(-1001);
    return (NewtonInt_V2(f,rand,aux,10,0.01));
}

// Function that calculates the 1st order Spline for density/field interpolation
//@param x argument of spline function
//@param L width of the spline box
double Spline1(double x, double L){
    if(x<L && x>-L) return 1/L*(1-fabs(x)/L);
    return 0;
}