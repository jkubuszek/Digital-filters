#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "window.h"

struct FilterCoeffs {
    std::vector<double> b;
    std::vector<double> a;
};


class Filter{
private:
    
protected:
    std::string name_ = "";
    std::vector<double> b_coeffs = {};
    std::vector<double> a_coeffs = {};
public:
    Filter(std::string n, const std::vector<double> &b,  const std::vector<double> &a) : name_(n), b_coeffs(b), a_coeffs(a) {}

    virtual FilterCoeffs getCoeffs() const = 0;

    virtual void printCoeffs() const = 0;

    virtual std::vector<double> response(const std::vector<double> &x, const int y_len = -1) = 0;

    void applyWindow(const Window &win){
        if(b_coeffs.size() <= 1){
            std::cerr << "Error: cannot apply windows to a filter of size equal or less than 1" << std::endl;           
        } else { 
             if(win.size() != b_coeffs.size()){
                std::cerr << "Error: coeffs_b and window size do not match in applyWindow()" << std::endl;
                return;
            } else {
                const auto& w = win.getCoeffs();
                for(int n = 0; n < b_coeffs.size(); n++){
                    b_coeffs[n] *= w[n];
                }    
                return;    
            }
        }
    }

    std::string getName() const{
        return name_;
    }
    void print_name() const{
        std::cout << "filter name: " << name_ << std::endl; 
    }
    
    virtual ~Filter(){}
};