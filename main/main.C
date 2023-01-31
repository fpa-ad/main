#include "sim.h"
#include <random>
#include <iostream>
#include <chrono>

using namespace std;

double maxwellian(mt19937_64 &generator, double temp){
    normal_distribution<double> distribution(0,sqrt(temp));
    return distribution(generator);  
}

int main(){
    unsigned seed1 = std::chrono::system_clock::now().time_since_epoch().count();
    mt19937_64 generator(seed1);
    sim simulation=sim(100, 100, 0.1, 0.1, 0.001, 1, 20, {-1}, {{maxwellian}});
    return 0;
}