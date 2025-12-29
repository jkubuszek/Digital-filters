#include "fir.hpp"
#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>

void FIR::design_low_pass(int order, double cutoff_f, double fs)
{
    std::vector<double> b(order, 0.0);
    double n_cutoff_f = cutoff_f / fs;
    double center = (order - 1) / 2.0;

    for (int i = 0; i < order; i++)
    {
        if (i == center)
        {
            b[i] = 2.0 * n_cutoff_f;
        }
        else
        {
            double n = i - center;
            b[i] = (std::sin(2.0 * M_PI * n_cutoff_f * n) / (M_PI * n));
        }
    }
    b_coeffs.resize(b.size());
    b_coeffs = b;
    a_coeffs = {1.0};
}

void FIR::design_high_pass(int order, double cutoff_f, double fs)
{
    std::vector<double> b(order, 0.0);
    double n_cutoff_f = cutoff_f / fs;
    double center = (order - 1) / 2.0;

    for (int i = 0; i < order; i++)
    {
        if (i == center)
        {
            b[i] = (1.0 - (2.0 * n_cutoff_f));
        }
        else
        {
            double n = i - center;
            b[i] = (std::sin(-2.0 * M_PI * n_cutoff_f * n) / (M_PI * n));
        }
    }
    b_coeffs.resize(b.size());
    b_coeffs = b;
    a_coeffs = {1.0};
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

void FIR::printCoeffs() const 
{
    std::cout << "all " << name << " filter coefficients: b" << std::endl;
    std::cout << "[";
    for (int i = 0; i < b_coeffs.size(); i++)
    {
        std::cout << b_coeffs[i] << ",";
    }
    std::cout << "]" << std::endl;

    std::cout << "filter coeffincients a = 1.0 since it is a FIR filter" << std::endl;
}

FilterCoeffs FIR::getCoeffs() const 
{
    return {b_coeffs, {1.0}};
}

void FIR::setCoeffs(const std::vector<double> &b, const std::vector<double> &a) 
{
    b_coeffs = b;
    a_coeffs = {1.0};
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
        for (int m = 0; m < b_coeffs.size(); m++)
        {
            if ((0 <= (n - m)) && ((n - m) < x.size()))
            {
                res += b_coeffs[m] * x[n - m];
            }
        }
        y[n] = res;
    }
    return y;
}

