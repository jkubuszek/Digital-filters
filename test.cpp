
#define _USE_MATH_DEFINES
#include <iostream>
#include "hamming.h"
#include "fir.h"


int main(){
    std::vector<double> fir_coeffs = {1.0,2.0,3.0,4.0,5.0};
    FIR f1(fir_coeffs);
    // f1.printCoeffs();
    
    Hamming h1(10);
    // h1.printCoeffs();

    std::vector<double> x = {};
    int x_size = 10;
    x.resize(x_size);
    for(int i =0; i < x_size; i++){
        x[i] = (double)i;
    }
    std::vector<double> y = f1.windowed_response(x,h1);
    return 0;
}
