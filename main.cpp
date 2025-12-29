
#define _USE_MATH_DEFINES
#include <iostream>
#include "hamming.hpp"
#include "fir.hpp"
#include "iir.hpp"
#include "sciplot/sciplot.hpp"
#include <random>
#include "plots.hpp"


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
    std::vector<double> iir_coeffs_b = {0.1}; 
    std::vector<double> iir_coeffs_a = {1.0, -0.9};
    FIR fir(fir_coeffs);
    IIR iir(iir_coeffs_b, iir_coeffs_a);

    Hamming h1(fir_coeffs.size());
    Hamming h2(iir_coeffs_b.size());

    //filters showcase
    // int x_size = 20;
    // std::vector<double> impulse(x_size,0.0);
    // impulse[0] = 1.0; //single impulse, 19 - zero-padding

    // fir.applyWindow(h1);
    // iir.applyWindow(h2);
    
    // std::vector sine = noisy_sine(200, 0.1, 1, 0.1);
    // std::vector<double> y_fir = fir.response(sine);
    // std::vector<double> y_iir = iir.response(impulse);
   
    // plot2d(sine, "sine");
    // plot2d(y_fir, "fir");
    // plot2d(impulse,"single impulse");
    // plot2d(y_iir, "iir");


    // lowpass, highpass filters and bodeplot showcase
    // int fs = 1000;
    // FIR lowpass;
    // lowpass.design_low_pass(20, 400, fs);
    // Hamming hamming(lowpass.getCoeffs().b.size());
    // plot2d(lowpass.bode(fs).freq, lowpass.bode(fs).mag_db, "lowpass bode without window");
    // lowpass.applyWindow(hamming);
    // plot2d(lowpass.bode(fs).freq, lowpass.bode(fs).mag_db, "lowpass bode with hamming window");

    
    // FIR highpass;
    // highpass.design_high_pass(20, 400, fs);    
    // plot2d(highpass.bode(fs).freq, highpass.bode(fs).mag_db, "highpass bode without window");
    // highpass.applyWindow(hamming);
    // plot2d(highpass.bode(fs).freq, highpass.bode(fs).mag_db, "highpass bode with hamming window");
    
    return 0;
}