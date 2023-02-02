#ifndef __UTILS__
#define __UTILS__

#include <iostream>
#include <iomanip>
#include <ctime>
#include <string>

typedef double (*func)(void); // type for conciseness
typedef double (*funcdouble)(double); // type for conciseness

std::string current_time();

double random_pos();

double random_speed();

double Newton(funcdouble f, double a, double x0, int iterations, double h);

double Integral(funcdouble f, double a, double b, double h);

double InverseCDF(funcdouble f, double rand);

#endif