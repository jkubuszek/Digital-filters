#pragma once
#include "filter.hpp"

namespace JK{
    class FIR : public Filter{
    private:

        void design_low_pass(int order, double cutoff_f, double fs);
        void design_high_pass(int order, double cutoff_f, double fs);

    public:

        enum class FilterType {LowPass, HighPass};

        FIR(const std::vector<double> &b);
        FIR();
        FIR(FilterType type, int order, double cutoff_f, double fs);

        void printCoeffs() const override;
        
        FilterCoeffs getCoeffs() const override;

        void setCoeffs(const std::vector<double> &b, const std::vector<double> &a)override;

        std::vector<double> response(const std::vector<double> &x, const int y_len = -1) override;
    };
}