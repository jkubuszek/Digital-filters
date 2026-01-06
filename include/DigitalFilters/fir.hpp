/**
 * @file fir.hpp
 * @author JK 
 * @brief This file handles the FIR class, which is a child class of Filter
 * @date 2026-01-02
 */
#pragma once
#include "filter.hpp"

namespace JK{
    /// @brief FIR class, FIR is a Finite Impulse Response filter
    class FIR : public Filter{
    private:
        /// @brief private method for designing low-pass FIR filters
        /// @param order order
        /// @param cutoff_f cutoff frequency
        /// @param fs sampling frequency
        void design_low_pass(int order, double cutoff_f, double fs);

        /// @brief private method for designing high-pass FIR filters, 
        /// @param order order, needs to be odd, even order will return an error
        /// @param cutoff_f cutoff frequency
        /// @param fs sampling frequency
        void design_high_pass(int order, double cutoff_f, double fs);

    public:
        /// @brief variable containing types od filters for one of the constructors 
        enum class FilterType {LowPass, HighPass};

        /// @brief constructor supporting custom coefficients
        /// @param b feedforward coefficients
        FIR(const std::vector<double> &b);

        /// @brief default constructor
        FIR();

        /// @brief advanced constructor that designs a low- or high-pass filters 
        /// @param type desired filter type (LowPass, Highpass)
        /// @param order order
        /// @param cutoff_f cutoff frequency
        /// @param fs sampling frequency
        FIR(FilterType type, int order, double cutoff_f, double fs);

        /// @brief getter for filter coefficients
        /// @return returns a structure holding both feedforward and feedback coefficients
        FilterCoeffs getCoeffs() const override;

        /// @brief helper method for overloaded << operator
        /// @param os output stream
        void print(std::ostream& os) const override;

        /// @brief setter for filter's coefficients
        /// @param b feedforward coefficients
        /// @param a feedback coefficients, since it is a FIR, they are defaulted to {1.0} no matter the input 
        void setCoeffs(const std::vector<double> &b, const std::vector<double> &a)override;

        /// @brief method for calculating filter's response to a given signal
        /// @param x vector containing signal samples
        /// @param y_len desired output length, defaults to length of the signal vector if not specified
        /// @return returns a vector with calculated response of the filter
        std::vector<double> response(const std::vector<double> &x, const int y_len = -1) override;
    };
}