/**
 * @file hamming.hpp
 * @author JK 
 * @brief This file handles the Hamming class, which is a child class of Window
 * @date 2026-01-02
 */
#pragma once
#include "window.hpp"
#include "filter.hpp"

namespace JK{
    /// @brief Hamming window class
    class Hamming : public Window{
    public:
        /// @brief constructor supporting a custom number of coefficients
        /// @param N number of coefficients
        Hamming(size_t N);

        /// @brief constructor supporting a number of coefficients based on a referenced Filter class object
        /// @param f Filter class object
        Hamming(const Filter &f);

        /// @brief default constructor
        Hamming();
    };
}