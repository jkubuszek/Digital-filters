
#define _USE_MATH_DEFINES
#include <iostream>
#include "DigitalFilters/hamming.hpp"
#include "DigitalFilters/fir.hpp"
#include "DigitalFilters/iir.hpp"
#include "sciplot/sciplot.hpp"
#include <random>
#include "DigitalFilters/plots.hpp"


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
    try{
        std::vector<double> fir_coeffs(10, 0.1); //smoothing filter
        std::vector<double> iir_coeffs_b = {0.1}; 
        std::vector<double> iir_coeffs_a = {1.0, -0.9};
        JK::FIR fir(fir_coeffs);
        JK::IIR iir(iir_coeffs_b, iir_coeffs_a);

        int fs = 1000;

        JK::FIR lowpass(JK::FIR::FilterType::LowPass, 20, 400, fs);
        JK::Hamming h_lowpass(lowpass);
        lowpass.applyWindow(h_lowpass);

        JK::FIR highpass(JK::FIR::FilterType::HighPass, 21, 400, fs);
        JK::Hamming h_highpass(highpass);
        highpass.applyWindow(h_highpass);


        std::vector sine = noisy_sine(200, 0.1, 1, 0.1);

        highpass.responsePlot(sine);
        lowpass.responsePlot(sine);

        highpass.bodePlot(fs);
        lowpass.bodePlot(fs);

        std::cout << highpass << std::endl;
        std::cout << lowpass << std::endl;


    } catch(const std::exception &e){
        std::cerr << "CRITICAL ERROR: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}