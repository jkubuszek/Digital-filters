#pragma once
#include "window.hpp"
#include "filter.hpp"

namespace JK{
    class Hanning : public Window{
    public:
        Hanning(size_t N);
        Hanning(const Filter &f);
        Hanning();
    };
}