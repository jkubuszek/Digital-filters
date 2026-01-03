#include "DigitalFilters/fir.hpp"
#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <stdexcept> 

namespace JK{
    void FIR::design_low_pass(int order, double cutoff_f, double fs){   
        if(order <= 0 || fs <= 0){
            throw std::invalid_argument("Error: Filter order and sampling frequency must be positive.");
        }
        if(cutoff_f <= 0 || cutoff_f >= fs / 2){
            throw std::invalid_argument("Error: Cutoff frequency must be positive and less than fs/2 (Nyquist limit).");
        }
        
        std::vector<double> b(order, 0.0);
        double n_cutoff_f = cutoff_f / fs;
        double center = (order - 1) / 2.0;

        for (int i = 0; i < order; i++){
            if(i == center){
                b[i] = 2.0 * n_cutoff_f;
            } else {
                double n = i - center;
                b[i] = (std::sin(2.0 * M_PI * n_cutoff_f * n) / (M_PI * n));
            }
        }
        coeffs.b.resize(b.size());
        coeffs.b = b;
        coeffs.a = {1.0};
    }

    void FIR::design_high_pass(int order, double cutoff_f, double fs){   

        if(order <= 0 || fs <= 0){
            throw std::invalid_argument("Error: Filter order and sampling frequency must be positive.");
        }
        if(cutoff_f <= 0 || cutoff_f >= fs / 2){
            throw std::invalid_argument("Error: Cutoff frequency must be positive and less than fs/2 (Nyquist limit).");
        }
        if(order % 2 == 0){
            throw std::invalid_argument("Error: Filter order must be odd");
        }

        std::vector<double> b(order, 0.0);
        double n_cutoff_f = cutoff_f / fs;
            double center = (order - 1) / 2.0;

            for (int i = 0; i < order; i++){
                if (i == center){
                    b[i] = (1.0 - (2.0 * n_cutoff_f));
                } else {
                    double n = i - center;
                    b[i] = (std::sin(-2.0 * M_PI * n_cutoff_f * n) / (M_PI * n));
                }
            }
            coeffs.b = b;
            coeffs.a = {1.0};
        
    }

    FIR::FIR(const std::vector<double> &b) : Filter("FIR", b, {1.0}) {}

    FIR::FIR() : Filter() {}

    FIR::FIR(FilterType type, int order, double cutoff_f, double fs) : Filter()
    {
        switch (type)
        {
        case FilterType::LowPass:
            design_low_pass(order, cutoff_f, fs);
            name = "FIR LowPass";
            break;
        case FilterType::HighPass:
            design_high_pass(order, cutoff_f, fs);
            name = "FIR HighPass";
            break;
        }
    }
    
    void FIR::print(std::ostream& os) const {
        os << "Filter Name: " << name << "\n";
        os << "Type: FIR (Finite Impulse Response)\n";
        os << "Feedforward coefficients b: [";
        for (size_t i = 0; i < coeffs.b.size(); i++) {
            os << coeffs.b[i] << (i < coeffs.b.size() - 1 ? ", " : "");
        }
        os << "]\n";
        os << "Feedback coefficients a: [1.0] (Since it is a FIR)";
    }

    FilterCoeffs FIR::getCoeffs() const 
    {
        return {coeffs.b, {1.0}};
    }

    void FIR::setCoeffs(const std::vector<double> &b, const std::vector<double> &a) 
    {
        coeffs.b = b;
        coeffs.a = {1.0};
    }

    std::vector<double> FIR::response(const std::vector<double> &x, const int y_len) 
    {
        int y_length;
        if (y_len > 0)
        {
            y_length = (size_t)y_len;
        }
        else
        {
            y_length = x.size();
        }
        std::vector<double> y(y_length, 0.0);
        for (int n = 0; n < y_length; n++)
        { // calculating the response
            double res = 0.0;
            for (int m = 0; m < coeffs.b.size(); m++)
            {
                if ((0 <= (n - m)) && ((n - m) < x.size()))
                {
                    res += coeffs.b[m] * x[n - m];
                }
            }
            y[n] = res;
        }
        return y;
    }
}
