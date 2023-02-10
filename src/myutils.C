#include "myutils.h"
#include <sstream>
#include <random>
#include <iostream>

using namespace std;

string current_time() {
    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);
    stringstream ss;
    ss << std::put_time(&tm, "%d-%m-%Y_%H-%M-%S");
    return ss.str();
}

double random_pos() {
    random_device rd;  // Will be used to obtain a seed for the random number engine
    mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
    uniform_real_distribution<> dis(0, 1);
    return dis(gen);
}

double random_speed() {
    random_device rd;  // Will be used to obtain a seed for the random number engine
    mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
    uniform_real_distribution<> dis(-1, 1);
    return dis(gen);
}

double Newton(funcdouble f, double a, double x0, int iterations, double h){
    while(f(x0)<0.001){
        x0+=1;
    }
    for (int i=0; i<iterations; ++i){
        x0=x0-((f(x0)-a)*2*h)/(f(x0+h)-f(x0-h));
    }
    return x0;
}

double NewtonInt_X(funcdouble f, double a, double x0, int iterations, double h){
    for (int i=0; i<iterations; ++i){
        x0=x0-((Integral(f,0,x0,0.01)-a)*2*h)/(Integral(f, 0,x0+h,0.01)-Integral(f, 0,x0-h,0.01));
    }
    return x0;
}


double NewtonInt_V(funcdouble f, double a, double x0, int iterations, double h){
    for (int i=0; i<iterations; ++i){
        x0=x0-((Integral(f,-1,x0,0.001)-a)*2*h)/(Integral(f,-1,x0+h,0.001)-Integral(f,-1,x0-h,0.001));
    }
    return x0;
}

double NewtonInt_V2(funcdouble f, double a, double x0, int iterations, double h){
    for (int i=0; i<iterations; ++i){
        x0=x0-((Integral(f,-10,x0,0.01)-a)*2*h)/(Integral(f,-10,x0+h,0.01)-Integral(f,-10,x0-h,0.01));
    }
    return x0;
}


double Integral(funcdouble f, double a, double b, double h){
    double res=0;
    int iters=(int)((b-a)/h);
    h=(b-a)/iters;
    for (int i=0; i<iters; ++i){
        res+=f(a+i*h)*h;
    }
    return res;
}

double InverseCDF_X(funcdouble f, double rand){
    double aux=f(-1001);
    return (NewtonInt_X(f,rand,aux,10,0.01));
}

double InverseCDF_V(funcdouble f, double rand){
    double aux=f(-1001);
    return (NewtonInt_V(f,rand,aux,10,0.001));
}

double InverseCDF_V2(funcdouble f, double rand){
    double aux=f(-1001);
    return (NewtonInt_V2(f,rand,aux,10,0.01));
}

double Spline1(double x, double L){
    if(x<L && x>-L) return 1/L*(1-fabs(x)/L);
    return 0;
}