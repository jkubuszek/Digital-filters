#include "DigitalFilters/filter.hpp"
#include <iostream>
#define _USE_MATH_DEFINES
#include <cmath>
#include "DigitalFilters/window.hpp"
#include "DigitalFilters/plots.hpp"
#include <stdexcept>

namespace JK{
    Filter::Filter(std::string n, const std::vector<double> &b, const std::vector<double> &a) : name(n), coeffs{b,a} {
        if(coeffs.b.size() <= 1){
            throw std::length_error("Error: Filter constructor error: "
                "Cannot create a filter with less than 2 b-coefficients.");
        }
    }
    Filter::Filter(){
        coeffs.b = {0.0, 0.0};
        coeffs.a = {1.0};
        name = "";
    }

    bool Filter::operator==(const Filter& other) const {
        return this->coeffs == other.coeffs; 
    }

    bool Filter::operator!=(const Filter& other) const {
        return this->coeffs != other.coeffs; 
    }
    std::ostream& operator<<(std::ostream& os, const Filter& f) {
        f.print(os); 
        return os;
    }

    void Filter::responsePlot(const std::vector<double> &x, const int y_len){
        std::vector<double> resp = response(x, y_len);
        plot2d(resp, name + " response plot");

    }

    void Filter::applyWindow(const Window &win){
        if(win.size() != coeffs.b.size()){
            throw std::invalid_argument("Error: Filter coefficients and window size do not match.");
        }
        const auto &w = win.getCoeffs();
        for (int n = 0; n < coeffs.b.size(); n++){
            coeffs.b[n] *= w[n];
        }
        return;
    }

    BodeData Filter::bode(double fs, int plot_points) const{
        BodeData data;
        for (int i = 0; i < plot_points; i++){
            double f = fs / 2.0 * (double)i / (plot_points - 1);
            double omega = 2 * M_PI * f / fs;

            std::complex<double> z = std::polar(1.0, -omega);

            std::complex<double> num(0.0, 0.0); // transfer function numerator
            for (size_t k = 0; k < coeffs.b.size(); k++){
                num += coeffs.b[k] * std::pow(z, (double)k);
            }

            std::complex<double> den(0.0, 0.0); // transfer function denumerator
            for (size_t k = 0; k < coeffs.a.size(); k++){
                den += coeffs.a[k] * std::pow(z, (double)k);
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

    Filter::~Filter(){}
}