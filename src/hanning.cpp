#define _USE_MATH_DEFINES
#include <iostream>
#include "DigitalFilters/hanning.hpp"
#include <cmath>

namespace JK{
    Hanning::Hanning(size_t N) : Window("Hanning") { 
        coeffs.resize(N);
        for(int i = 0; i < N; i++){
            coeffs[i] = 0.5*(1-std::cos(2*M_PI*i/((double)N - 1)));
        }
    }

    Hanning::Hanning(const Filter &f) : Window("Hanning") { 
        size_t N = f.getCoeffs().b.size();
        coeffs.resize(N);
        for(int i = 0; i < N; i++){
            coeffs[i] = 0.5*(1-std::cos(2*M_PI*i/((double)N - 1)));
        }
    }

    Hanning::Hanning() : Window(){}
}