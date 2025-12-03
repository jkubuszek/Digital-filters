#pragma once
#include <iostream>
#include <string.h>
#include <vector>
#include "filter.h"
#include "hamming.h"


class FIR : public Filter{
private:
    std::vector<double> coeffs_ = {};
    size_t size_ = coeffs_.size();

public:
    FIR(std::vector<double> &c) : coeffs_(c), Filter("FIR") {}
    
    void printCoeffs() const override{
        std::cout << "all " << name_ << " filter coefficients:" << std::endl;
        std::cout << "["; 
        for(int i = 0; i < size_; i++){
            std::cout << coeffs_[i] << ",";
        }
        std::cout << "]" << std::endl;   
    }
    
    std::vector<double> getCoeffs() const override{
        return coeffs_;
    }

    std::vector<double> response(const std::vector<double> &x) override{
        int y_length = x.size() + coeffs_.size() - 1;
        std::vector<double> y = {};
        for (int n = 0; n < y_length; n++){ //calculating the response
            double res = 0.0;
            for (int m = 0; m < coeffs_.size(); m++){
                if ((0 <= (n-m)) && ((n-m) <= x.size())){
                    res += coeffs_[m]*x[n-m];
                }
            }
            y.push_back(res);                
        }
        return y;
    }

    std::vector<double> windowed_response(const std::vector<double> &x, const Window &win) override{
        if(win.size() != x.size()){
            std::cerr << "Error: input and window size do not match in windowed_response()" << std::endl;
            return {};
        } else {
            std::vector<double> y = response(x);
            const auto& w = win.getCoeffs();
            for(int n = 0; n < size(x); n++){
                y[n] *= w[n];
            }        
            std::cout << "windowed response:" << std::endl;
            std::cout << "["; 
            for(int i = 0; i < y.size(); i++){
                std::cout << y[i] << ",";
            }
            std::cout << "]" << std::endl;   
    
            return y;
        }
    }
    
};