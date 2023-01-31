#ifndef __UTILS__
#define __UTILS__

#include <iostream>
#include <iomanip>
#include <ctime>
#include <string>

typedef double (*func)(void); // type for conciseness

std::string current_time();

double random_pos();

double random_speed();

#endif