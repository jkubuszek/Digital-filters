#pragma once
#include <iostream>
#include <string.h>
#include <vector>
#include "filter.h"
#include "hamming.h"


class IIR : public Filter{
private:
public:
    IIR(const std::vector<double> &b, const std::vector<double> &a) : Filter("IIR", b, a){
        if(a_coeffs.empty() || a_coeffs[0] == 0.0) {
            a_coeffs = {1.0};
        }
    }
    
    void printCoeffs() const override{
        std::cout << "all " << name_ << " filter coefficients: b" << std::endl;
        std::cout << "["; 
        for(int i = 0; i < b_coeffs.size(); i++){
            std::cout << b_coeffs[i] << ",";
        }
        std::cout << "]" << std::endl;   

        std::cout << "all " << name_ << " filter coefficients: a" << std::endl;
        std::cout << "["; 
        for(int i = 0; i < a_coeffs.size(); i++){
            std::cout << a_coeffs[i] << ",";
        }
        std::cout << "]" << std::endl;   
    }
    
    FilterCoeffs getCoeffs() const override{
        return {b_coeffs, a_coeffs};
    }

std::vector<double> response(const std::vector<double> &x, const int y_len = -1) override{
    int y_size;
    if (y_len > 0) {
            y_size = (size_t)y_len;
        } else {
            y_size = x.size();
        }
        double a0 = a_coeffs[0];
        std::vector<double> y(y_size, 0.0);
        for(int n = 0; n < x.size(); n++){
            double sum_b = 0.0;
            double sum_a = 0.0;
            for(int m = 0; m < b_coeffs.size(); m++){
                if((0 <= (n-m)) && ((n-m) < x.size())){
                    sum_b += b_coeffs[m]*x[n-m];
                }
            }
            for(int k = 1; k < a_coeffs.size(); k++){
                if((0 <= (n-k)) && ((n-k) < y.size())){
                    sum_a += a_coeffs[k]*y[n-k];
                }
            }
            y[n] = (sum_b - sum_a)/a0;
        }
       return y;
    }
};