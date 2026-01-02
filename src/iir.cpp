#include <iostream>
#include "DigitalFilters/iir.hpp"

namespace JK{
    IIR::IIR(const std::vector<double> &b, const std::vector<double> &a) : Filter("IIR", b, a){
        if(coeffs.a.empty() || coeffs.a[0] == 0.0) {
            coeffs.a = {1.0};
        }
    }
    IIR::IIR() : Filter(){}

    void IIR::printCoeffs() const{
        std::cout << "all " << name << " filter coefficients: b" << std::endl;
        std::cout << "["; 
        for(int i = 0; i < coeffs.b.size(); i++){
            std::cout << coeffs.b[i] << ",";
        }
        std::cout << "]" << std::endl;   

        std::cout << "all " << name << " filter coefficients: a" << std::endl;
        std::cout << "["; 
        for(int i = 0; i < coeffs.a.size(); i++){
            std::cout << coeffs.a[i] << ",";
        }
        std::cout << "]" << std::endl;   
    }

    FilterCoeffs IIR::getCoeffs() const{
        return {coeffs.b, coeffs.a};
    }

    std::vector<double> IIR::response(const std::vector<double> &x, const int y_len){
        int y_size;
        if (y_len > 0) {
                y_size = (size_t)y_len;
            } else {
                y_size = x.size();
            }
            double a0 = coeffs.a[0];
            std::vector<double> y(y_size, 0.0);
            for(int n = 0; n < x.size(); n++){
                double sum_b = 0.0;
                double sum_a = 0.0;
                for(int m = 0; m < coeffs.b.size(); m++){
                    if((0 <= (n-m)) && ((n-m) < x.size())){
                        sum_b += coeffs.b[m]*x[n-m];
                    }
                }
                for(int k = 1; k < coeffs.a.size(); k++){
                    if((0 <= (n-k)) && ((n-k) < y.size())){
                        sum_a += coeffs.a[k]*y[n-k];
                    }
                }
                y[n] = (sum_b - sum_a)/a0;
            }
        return y;
        }
        
    void IIR::setCoeffs(const std::vector<double> &b, const std::vector<double> &a){
        coeffs.b = b;
        coeffs.a = a;
    }
}