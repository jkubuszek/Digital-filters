#define _USE_MATH_DEFINES
#include "DigitalFilters/hamming.hpp"
#include <cmath>

namespace JK{
    Hamming::Hamming(size_t N) : Window("Hamming") { 
        coeffs.resize(N);
        for(int i = 0; i < N; i++){
            coeffs[i] = 0.54-0.46*std::cos(2*M_PI*i/((double)N - 1));
        }
    }

    Hamming::Hamming(const Filter &f) : Window("Hamming") { 
        size_t N = f.getCoeffs().b.size();
        coeffs.resize(N);
        for(int i = 0; i < N; i++){
            coeffs[i] = 0.54-0.46*std::cos(2*M_PI*i/((double)N - 1));
        }
    }

    Hamming::Hamming() : Window(){}
}