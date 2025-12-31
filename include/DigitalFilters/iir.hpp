#pragma once
#include "filter.hpp"

namespace JK{
    class IIR : public Filter{
    public:

        IIR(const std::vector<double> &b, const std::vector<double> &a);
        IIR();
        
        void printCoeffs() const override;   
        
        FilterCoeffs getCoeffs() const override;

        std::vector<double> response(const std::vector<double> &x, const int y_len = -1) override;
        
        void setCoeffs(const std::vector<double> &b, const std::vector<double> &a)override;
    };
}