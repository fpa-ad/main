#ifndef __UTILS__
#define __UTILS__

#include <iostream>
#include <iomanip>
#include <ctime>
#include <string>
#include <functional>

// Definition of type; pointer to function void -> double
typedef double (*func)(void); 

// Definition of type; function double -> double
typedef std::function<double(double)> funcdouble;

// Function to get current time; used to name folders
std::string current_time();

// Function to get a Newton's method approximation of the solution to f(x)=a
//@param f function to apply Newton's method to
//@param a constant on the RHS of the equation f(x) = a
//@param x0 initial value for x
//@param iterations number of iterations of Newton's method
//@param h finite difference to calculate the derivative of the denominator of the method
double Newton(funcdouble f, double a, double x0, int iterations, double h);

// Function to get a Newton's method approximation of the solution to \int_{-\infty}^{x} f(t) dt = a (parameters optimized for position initialization)
//@param f function whose integral to apply Newton's method to
//@param a constant on the RHS of the equation f(x) = a
//@param x0 initial value for x
//@param iterations number of iterations of Newton's method
//@param h finite difference to calculate the derivative of the denominator of the method
double NewtonInt_X(funcdouble f, double a, double x0, int iterations, double h);

// Function to get a Newton's method approximation of the solution to \int_{-\infty}^{x} f(t) dt = a (parameters optimized for low velocity initialization)
//@param f function whose integral to apply Newton's method to
//@param a constant on the RHS of the equation f(x) = a
//@param x0 initial value for x
//@param iterations number of iterations of Newton's method
//@param h finite difference to calculate the derivative of the denominator of the method
double NewtonInt_V(funcdouble f, double a, double x0, int iterations, double h);

// Function to get a Newton's method approximation of the solution to \int_{-\infty}^{x} f(t) dt = a (parameters optimized for high velocity initialization)
//@param f function whose integral to apply Newton's method to
//@param a constant on the RHS of the equation f(x) = a
//@param x0 initial value for x
//@param iterations number of iterations of Newton's method
//@param h finite difference to calculate the derivative of the denominator of the method
double NewtonInt_V2(funcdouble f, double a, double x0, int iterations, double h);

// Function to calculate the integral of f, over the interval [a,b]
//@param f function to calculate the integral of
//@param a beginning of interval
//@param a end of interval
//@param h spacing between sampled points
double Integral(funcdouble f, double a, double b, double h);

// Function to calculate a random initial position
//@param f position distribution function
//@param rand random value between 0 and 1 to seed the random position
double InverseCDF_X(funcdouble f, double rand);

// Function to calculate a random initial (low) velocity
//@param f velocity distribution function
//@param rand random value between 0 and 1 to seed the random velocity
double InverseCDF_V(funcdouble f, double rand);

// Function to calculate a random initial (high) velocity
//@param f velocity distribution function
//@param rand random value between 0 and 1 to seed the random velocity
double InverseCDF_V2(funcdouble f, double rand);

// Function that calculates the 1st order Spline for density/field interpolation
//@param x argument of spline function
//@param L width of the spline box
double Spline1(double x, double L);

#endif