#ifndef __UTILS__
#define __UTILS__

#include <iostream>
#include <iomanip>
#include <ctime>
#include <string>
#include <functional>

typedef double (*func)(void); // type for conciseness
//typedef double (*funcdouble)(double); // type for conciseness
typedef std::function<double(double)> funcdouble;

std::string current_time();

double random_pos();

double random_speed();

double Newton(funcdouble f, double a, double x0, int iterations, double h);

double NewtonInt_X(funcdouble f, double a, double x0, int iterations, double h);

double NewtonInt_V(funcdouble f, double a, double x0, int iterations, double h);

double NewtonInt_V2(funcdouble f, double a, double x0, int iterations, double h);

double Integral(funcdouble f, double a, double b, double h);

double InverseCDF_X(funcdouble f, double rand);

double InverseCDF_V(funcdouble f, double rand);

double InverseCDF_V2(funcdouble f, double rand);

double Spline1(double x, double L);

#endif