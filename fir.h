#pragma once
#include <iostream>
#include <string.h>
#include <vector>
#include "filter.h"
#include "hamming.h"


class FIR : public Filter{
private:
public:
    FIR(const std::vector<double> &b) : Filter("FIR", b, {1.0}) {}
    
    void printCoeffs() const override{
        std::cout << "all " << name_ << " filter coefficients: b" << std::endl;
        std::cout << "["; 
        for(int i = 0; i < b_coeffs.size(); i++){
            std::cout << b_coeffs[i] << ",";
        }
        std::cout << "]" << std::endl;   

       std::cout << "filter coeffincients a = 1.0 since it is a FIR filter" << std::endl;  
    }
    
    FilterCoeffs getCoeffs() const override{
        return { b_coeffs, {1.0} };
    }

    std::vector<double> response(const std::vector<double> &x, const int y_len = -1) override{
        int y_length;
        if (y_len > 0) {
            y_length = (size_t)y_len;
        } else {
            y_length = x.size();
        }
        std::vector<double> y(y_length, 0.0);
        for (int n = 0; n < y_length; n++){ //calculating the response
            double res = 0.0;
            for (int m = 0; m < b_coeffs.size(); m++){
                if ((0 <= (n-m)) && ((n-m) < x.size())){
                    res += b_coeffs[m]*x[n-m];
                }
            }
            y[n] = res;                
        }
        return y;
    }
};