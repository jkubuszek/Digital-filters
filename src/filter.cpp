#include "filter.hpp"
#include <iostream>
#define _USE_MATH_DEFINES
#include <cmath>
#include "window.hpp"
#include "plots.hpp"

Filter::Filter(std::string n, const std::vector<double> &b, const std::vector<double> &a) : name(n), b_coeffs(b), a_coeffs(a) {}
Filter::Filter(){
    b_coeffs = {0.0};
    a_coeffs = {1.0};
    name = "";
}

void Filter::applyWindow(const Window &win){
    if (b_coeffs.size() <= 1){
        std::cerr << "Error: cannot apply windows to a filter of size equal or less than 1" << std::endl;
    }
    else {
        if (win.size() != b_coeffs.size())
        {
            std::cerr << "Error: coeffs_b and window size do not match in applyWindow()" << std::endl;
            return;
        }
        else {
            const auto &w = win.getCoeffs();
            for (int n = 0; n < b_coeffs.size(); n++){
                b_coeffs[n] *= w[n];
            }
            return;
        }
    }
}

BodeData Filter::bode(double fs, int plot_points) const{
    BodeData data;
    for (int i = 0; i < plot_points; i++){
        double f = fs / 2.0 * (double)i / (plot_points - 1);
        double omega = 2 * M_PI * f / fs;

        std::complex<double> z = std::polar(1.0, -omega);

        std::complex<double> num(0.0, 0.0); // transmitance numerator
        for (size_t k = 0; k < b_coeffs.size(); k++){
            num += b_coeffs[k] * std::pow(z, (double)k);
        }

        std::complex<double> den(0.0, 0.0); // transmitance denumerator
        for (size_t k = 0; k < a_coeffs.size(); k++){
            den += a_coeffs[k] * std::pow(z, (double)k);
        }
        std::complex<double> H = num / den; // calculating H

        double mag = std::abs(H);
        double db = 20.0 * std::log10(mag + 1e-9);

        double phase_rad = std::arg(H);
        double phase_deg = phase_rad * 180.0 / M_PI;

        data.freq.push_back(f);
        data.mag_db.push_back(db);
        data.phase_deg.push_back(phase_deg);
    }
    return data;
}

void Filter::bodePlot(double fs, int plot_points) const{
    BodeData data = bode(fs, plot_points);

    plot2d(data.freq, data.mag_db, name + " magnitude bode plot");
    plot2d(data.freq, data.phase_deg, name + " phase bode plot");
}

std::string Filter::getName() const{
    return name;
}

void Filter::setName(std::string n){
    name = n;
}

void Filter::printName() const{
    std::cout << "filter name: " << name << std::endl;
}
Filter::~Filter(){}