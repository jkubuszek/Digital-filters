
#define _USE_MATH_DEFINES
#include <iostream>
#include "hamming.h"
#include "fir.h"
#include "iir.h"
#include "sciplot/sciplot.hpp"
#include <random>
namespace sp = sciplot;
//compilation: g++ -std=c++17 -o test test.cpp -I.

void plot2d(const std::vector<double> &y, std::string name){
    sp::Plot2D plot;
    std::vector<double> x_axis;
    for(int i = 0; i < y.size(); i++){
        x_axis.push_back((double)i);
    }
    std::valarray<double> vx(x_axis.data(), x_axis.size());
    std::valarray<double> vy(y.data(), y.size());
    plot.drawCurve(vx, vy);
    sciplot::Figure fig = {{plot}}; 
    sp::Canvas canvas = {{fig}};
    canvas.save(name + ".pdf");
}
std::vector<double> noisy_sine(int size, double freq, double amp, double noise_level) {
    std::vector<double> signal;
    signal.reserve(size);

    //rng initialisation
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> noise(-noise_level, noise_level);
    for (int i = 0; i < size; i++) {
        double clean_val = amp*sin(freq*i);
        double noisy_val = clean_val + noise(gen);
        signal.push_back(noisy_val);
    }
    return signal;
}

int main(){
    std::vector<double> fir_coeffs(10, 0.1); //smoothing filter
    std::vector<double> iir_coeffs_b = {0.1}; //
    std::vector<double> iir_coeffs_a = {1.0, -0.9};
    FIR fir(fir_coeffs);
    IIR iir(iir_coeffs_b, iir_coeffs_a);

    Hamming h1(fir_coeffs.size());
    Hamming h2(iir_coeffs_b.size());

    int x_size = 20;
    std::vector<double> impulse(x_size,0.0);
    impulse[0] = 1.0; //single impulse, 19 - zero-padding

    // fir.applyWindow(h1);
    // iir.applyWindow(h2);
    
    std::vector sine = noisy_sine(200, 0.1, 1, 0.1);
    std::vector<double> y_fir = fir.response(sine);
    std::vector<double> y_iir = iir.response(impulse);
   
    plot2d(sine, "sine");
    plot2d(y_fir, "fir");
    plot2d(impulse,"single impulse");
    plot2d(y_iir, "iir");



    
    
    return 0;
}
