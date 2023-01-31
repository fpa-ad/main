#include "myutils.h"
#include <sstream>
#include <random>
#include <iostream>

using namespace std;

string current_time() {
    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);
    stringstream ss;
    ss << std::put_time(&tm, "%d-%m-%Y %H-%M-%S");
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