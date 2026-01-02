/**
 * @file plots.hpp
 * @author JK 
 * @brief This file contains plotting functions that use sciplot library to generate pdfs with plots
 * @date 2026-01-02
 */
#pragma once
#include <vector>
#include <string>

namespace JK{
    /// @brief overloaded 2d plotting function, that defaults the x axis to just sample numbers
    /// @param y input that will be plotted
    /// @param name desired pdf file name
    void plot2d(const std::vector<double> &y, std::string name);

    /// @brief overloaded 2d plotting function, that supports custom x axis
    /// @param x x axis vector
    /// @param y input vector
    /// @param name desired pdf file name
    void plot2d(const std::vector<double> &x, const std::vector<double> &y, std::string name);
}