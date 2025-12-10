#pragma once
#define _USE_MATH_DEFINES
#include <iostream>
#include <string>
#include <vector>
#include "window.h"
#include <cmath>

class Hamming : public Window{
private:

public:
    Hamming(size_t N) : Window("Hamming") { 
        coeffs_.resize(N);
        
        for(int i = 0; i < N; i++){
            coeffs_[i] = 0.54-0.46*std::cos(2*M_PI*i/((double)N - 1));
        }
    }
};