/**
 * @file hanning.hpp
 * @author JK 
 * @brief This file handles the Hanning class, which is a child class of Window
 * @date 2026-01-02
 */
#pragma once
#include "window.hpp"
#include "filter.hpp"

namespace JK{
    /// @brief Hanning window class
    class Hanning : public Window{
    public:
        /// @brief constructor supporting a custom number of coefficients
        /// @param N number of coefficients
        Hanning(size_t N);

        /// @brief constructor supporting a number of coefficients based on a referenced Filter class object
        /// @param f Filter class object
        Hanning(const Filter &f);

        /// @brief default constructor
        Hanning();
    };
}