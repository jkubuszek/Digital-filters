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
        /// @brief constructor supporting custom name
        /// @param n name 
        Window(std:: string n);

        /// @brief default constructor
        Window();

        /// @brief method for printing window's coefficients in terminal, for testing purposes
        void printCoeffs() const;
        
        /// @brief getter for window coefficients
        /// @return returns a vector containing windiw coefficients
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