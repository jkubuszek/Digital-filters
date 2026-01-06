/**
 * @file window.hpp
 * @author JK 
 * @brief This file handles the Window class
 * @date 2026-01-02
 */
#pragma once
#include <string>
#include <vector>

namespace JK{
    /// @brief Window class
    class Window{
    protected:
        /// @brief vector containing window coefficients
        std::vector<double> coeffs = {};
        /// @brief window's name
        std::string name = "";
        
    public:
        /// @brief overloaded == operator for comparing windows coefficients sets
        /// @param other other Window Class object
        /// @return returns 1 if window coeficients sets are the same, 0 if they are different
        bool operator==(const Window& other) const;

        /// @brief overloaded != operator for comparing windows coefficients sets
        /// @param other other Window Class object
        /// @return returns 0 if window coeficients sets are the same, 1 if they are different
        bool operator!=(const Window& other) const;

        /// @brief constructor supporting custom name
        /// @param n name 
        Window(std:: string n);

        /// @brief default constructor
        Window();

        /// @brief overloaded << operator for printing all coefficients into output stream
        /// @param os output stream
        /// @param w Window class object
        /// @return returns the output stream
        friend std::ostream& operator<<(std::ostream& os, const Window& w);
        
        /// @brief getter for window coefficients
        /// @return returns a vector containing window coefficients
        std::vector<double> getCoeffs() const;

        /// @brief getter for window's name
        /// @return returns a string containing filter's name
        std::string getName() const;

        /// @brief setter for filter's name
        /// @param n name
        void setName(std::string n);

        /// @brief method for getting the window's size (the size of the coefficients vector)
        /// @return returns a size_t variable containing window's size
        size_t size() const;

        /// @brief virtual destructor, for memory safety when using polymorphism
        virtual ~Window();
    };
}