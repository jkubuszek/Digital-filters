#pragma once
#define _USE_MATH_DEFINES
#include <string>
#include <vector>
#include <complex>
#include "window.hpp"

struct FilterCoeffs{
    std::vector<double> b;
    std::vector<double> a;
};
struct BodeData{
    std::vector<double> freq; 
    std::vector<double> mag_db; 
    std::vector<double> phase_deg;
};

class Filter{    
protected:
    std::string name;
    std::vector<double> b_coeffs = {};
    std::vector<double> a_coeffs = {};
public:
    Filter(std::string n, const std::vector<double> &b,  const std::vector<double> &a);
    Filter();

    virtual ~Filter();

    virtual FilterCoeffs getCoeffs() const = 0;

    virtual void printCoeffs() const = 0;

    virtual std::vector<double> response(const std::vector<double> &x, const int y_len = -1) = 0;

    //void responsePlot() //to do

    void applyWindow(const Window &win);

    BodeData bode(double fs, int plot_points = 200) const;

    void bodePlot(double fs, int plot_points = 200) const;

    virtual void setCoeffs(const std::vector<double> &b, const std::vector<double> &a)  = 0;

    std::string getName() const;

    void setName(std::string n);

    void printName() const;
};