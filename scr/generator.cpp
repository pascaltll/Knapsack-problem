#include "generator.h"
// cauchy_distribution
#include <iostream>
#include <random>

void generator (int n, std::vector<int>& weight, std::vector<int>& profit) {//number of data
    //int n = 100; //<<30000
    const int nrolls=10000*n;  // number of experiments
    const int nstars= 10*n;    // maximum number of stars to distribute

    std::default_random_engine generator;
    std::cauchy_distribution<double> distribution(n/2,n/10);//avg, min
    std::vector<int> p(n);
    for (size_t i = 0; i < nrolls; ++i) {
        double number = distribution(generator);
        if ((number >= 0) && (number < n)) {
            ++p[int(number)];
        }
    }
    for (size_t i = 0; i < n; ++i) {
        profit[i] = p[i]*nstars/nrolls;
    }
    /*std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<> distrib(1, 100);

    for (size_t i=0; i<10; ++i) {
       weight[i] =  distrib(gen);
    }*/

    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<> distrib(1, 10);//range

    for (int i=0; i< n; ++i) {
        weight[i] = (int)distrib(gen);
    }

}