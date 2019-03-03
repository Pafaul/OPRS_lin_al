#ifndef WHITE_NOISE_H
#define WHITE_NOISE_H
#include <random>
#include <iostream>
#include <string>
#include <chrono>
#include <math.h>
#include <fstream>
#include <string>
#include <cstdlib>
#include <sstream>

class white_noise
{
public:
    white_noise();
    ~white_noise();
    long double nu;
    long double t_corr;
    const long double w = 1000;
    long double get_nu(long double time);
    long double white_noise_generator();
    long double nu_0 = 0;
    long double time_temp = 0;
    int temp = 0;
};

#endif // WHITE_NOISE_H
