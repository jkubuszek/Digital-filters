/**
 * @file filter.hpp
 * @author JK 
 * @brief This file handles the base filter class
 * @date 2026-01-02
 */
#pragma once
#define _USE_MATH_DEFINES
#include <string>
#include <vector>
#include <complex>
#include "window.hpp"

namespace JK{
    /// @brief a structure for holding  both feedback (a) and feedforward (b) coefficients
    struct FilterCoeffs{

        std::vector<double> b; /// feedfoward coefficients
        std::vector<double> a; /// feedback coefficients, equals [1.0] for fir
        
        /// @brief overloaded == operator for comparing filter coefficients sets
        /// @param other other FilterCoeffs structure
        /// @return returns 1 if coeficients sets are the same, 0 if they are different
        bool operator==(const FilterCoeffs& other) const {
            return b == other.b && a == other.a;
        }

        /// @brief overloaded != operator for comparing filter coefficients sets
        /// @param other other FilterCoeffs structure
        /// @return returns 0 if coeficients sets are the same, 1 if they are different
        bool operator!=(const FilterCoeffs& other) const {
            return b != other.b || a != other.a;
        }
    };
    /// @brief a structure for holding  all the parameters needed for Bode plots
    struct BodeData{
        std::vector<double> freq; /// frequency index vector
        std::vector<double> mag_db; /// magnitutde in decibels corresponding to each element from freq vector
        std::vector<double> phase_deg; // phase in degrees corresponding to each element from freq vector
    };
    /// @brief Filter class representing a digital filter
    class Filter{    
    protected:
        /// @brief helper method for overloaded << operator
        /// @param os output stream
        virtual void print(std::ostream& os) const = 0;

        /// @brief filter' name
        std::string name;

        /// @brief structure holding filter's coefficients
        FilterCoeffs coeffs; 
    public:

        /// @brief overloaded == operator for comparing filter type and their coefficients sets
        /// @param other other Filter Class object
        /// @return returns 1 if filters coeficients sets are the same, 0 if they are different
        bool operator==(const Filter& other) const;
        
        /// @brief overloaded != operator for comparing filter type and their coefficients sets
        /// @param other other Filter Class object
        /// @return returns 0 if filters coeficients sets are the same, 1 if they are different
        bool operator!=(const Filter& other) const;
        
        /// @brief overloaded << operator for printing all the coefficients into ouput stream
        /// @param os ouput stream
        /// @param f Filter Class object
        /// @return returns the output stream
        friend std::ostream& operator<<(std::ostream& os, const Filter& f);

        /// @brief class constructor supporting custom coefficients
        /// @param n name of the filter
        /// @param b feedforward coefficients
        /// @param a feedback coefficients
        Filter(std::string n, const std::vector<double> &b,  const std::vector<double> &a);
       
        /// @brief default constructor
        Filter();
        
        /// @brief virtual destructor, for memory safety when using polymorphism
        virtual ~Filter();

       
        
        /// @brief getter for filter coefficients
        /// @return returns a structure holding both feedforward and feedback coefficients
        virtual FilterCoeffs getCoeffs() const = 0;

        /// @brief method for calculating filter's response to a given signal
        /// @param x vector containing signal samples
        /// @param y_len desired output length, defaults to length of the signal vector if not specified
        /// @return returns a vector with calculated reponse of the filter
        virtual std::vector<double> response(const std::vector<double> &x, const int y_len = -1) = 0;

        /// @brief method for plotting the filter's response to a given signal 
        /// @param x vector containing signal samples
        /// @param y_len desired output length, defaults to length of the signal vector if not specified
        void responsePlot(const std::vector<double> &x, const int y_len = -1);

        /// @brief method for applying a window to filter's coefficients
        /// @param win object of the Window class, representing a Hamming/Hanning window
        void applyWindow(const Window &win);

        /// @brief method for calculating filter's frequency response
        /// @param fs sampling frequency
        /// @param plot_points number of desired plot points, defaults to 200 if not specified
        /// @return returns frequency indexes and both magnitude in decibels and phase in degrees corresponding to each frequency index
        BodeData bode(double fs, int plot_points = 200) const;

        /// @brief method for plotting filter's frequency response, generates 2 pdf files, one for magnitude plot and one for phase plot
        /// @param fs sampling frequency
        /// @param plot_points number of desired plot points, defaults to 200 if not specified
        void bodePlot(double fs, int plot_points = 200) const;

        /// @brief setter for filter's coefficients
        /// @param b feedforward coefficients
        /// @param a feedback coefficients
        virtual void setCoeffs(const std::vector<double> &b, const std::vector<double> &a)  = 0;

        /// @brief getter for filter's name
        /// @return returns a string containing the name
        std::string getName() const;

        /// @brief setter for filter's name
        /// @param n name
        void setName(std::string n);
    };
}