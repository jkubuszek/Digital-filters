#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "window.h"
#include <complex>

struct FilterCoeffs {
    std::vector<double> b;
    std::vector<double> a;
};
struct BodeData {
    std::vector<double> freq; 
    std::vector<double> mag_db; 
};


class Filter{
private:
    
protected:
    std::string name = "";
    std::vector<double> b_coeffs = {};
    std::vector<double> a_coeffs = {};
public:
    Filter(std::string n, const std::vector<double> &b,  const std::vector<double> &a) : name(n), b_coeffs(b), a_coeffs(a) {}
    Filter(){
        b_coeffs = {0.0};
        a_coeffs = {0.0};
        name = "unnamed filter";
    }

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

    BodeData bode(const Filter &filter, double fs, int plot_points = 200){
        BodeData data;
        FilterCoeffs coeffs = filter.getCoeffs();
        
        for(int i = 0; i < plot_points; i++){       
            double f = fs/2.0 * i * (plot_points-1);   
            double omega = 2*M_PI*f/fs;

            std::complex<double> z = std::polar(1.0, -omega);

            std::complex<double> num(0.0, 0.0); //transmitance numerator
            for (size_t k = 0; k < coeffs.b.size(); k++) {
                num += coeffs.b[k] * std::pow(z, (double)k);
            }

            std::complex<double> den(0.0, 0.0); //transmitance denumerator
            for (size_t k = 0; k < coeffs.a.size(); k++) {
                den += coeffs.a[k] * std::pow(z, (double)k);
            }
            std::complex<double> H = num/den; //calculating H

            double mag = std::abs(H);
            double db = 20.0 * std::log10(mag + 1e-9);

            data.freq.push_back(f);
            data.mag_db.push_back(db);
        }
        return data;
    }


    virtual void setCoeffs(const std::vector<double> &b, const std::vector<double> &a)  = 0;

    std::string getName() const{
        return name;
    }
    void print_name() const{
        std::cout << "filter name: " << name << std::endl; 
    }
    
    virtual ~Filter(){}
};