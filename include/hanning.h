#pragma once
#define _USE_MATH_DEFINES
#include <iostream>
#include <string>
#include <vector>
#include "window.h"
#include <cmath>

class Hanning : public Window{
private:

public:
    Hanning(size_t N) : Window("Hanning") { 
        coeffs.resize(N);
        
        for(int i = 0; i < N; i++){
            coeffs[i] = 0.5*(1-std::cos(2*M_PI*i/((double)N - 1)));
        }
    }
    Hanning() : Window(){}
};