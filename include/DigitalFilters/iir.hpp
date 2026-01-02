/**
 * @file iir.hpp
 * @author JK 
 * @brief This file handles the IIR class, which is a child class of Filter
 * @date 2026-01-02
 */
#pragma once
#include "filter.hpp"

namespace JK{
    /// @brief IIR class, IIR is a Infinite Impulse Response filter
    class IIR : public Filter{
    public:
        /// @brief constructor supporting custom coefficients
        /// @param b feedforward coefficients
        /// @param a feedback coefficients
        IIR(const std::vector<double> &b, const std::vector<double> &a);
        
        /// @brief default constructor
        IIR();
        
        /// @brief method for printing coefficients in terminal, for testing purposes
        void printCoeffs() const override;   
        
        /// @brief getter for filter coefficients
        /// @return returns a structure holding both feedforward and feedback coefficients
        FilterCoeffs getCoeffs() const override;
        
        /// @brief method for calculating filter's response to a given signal
        /// @param x vector containing signal samples
        /// @param y_len desired output length, defaults to length of the signal vector if not specified
        /// @return returns a vector with calculated reponse of the filter
        std::vector<double> response(const std::vector<double> &x, const int y_len = -1) override;
        
        /// @brief setter for filter's coefficients
        /// @param b feedforward coefficients
        /// @param a feedback coefficients
        void setCoeffs(const std::vector<double> &b, const std::vector<double> &a)override;
    };
}