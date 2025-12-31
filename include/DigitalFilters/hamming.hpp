#pragma once
#include "window.hpp"
#include "filter.hpp"

namespace JK{
    class Hamming : public Window{
    public:
        Hamming(size_t N);
        Hamming(const Filter &f);
        Hamming();
    };
}