#pragma once
#define _USE_MATH_DEFINES
#include <iostream>
#include <string>
#include <vector>
#include "window.hpp"
#include <cmath>

class Hanning : public Window{
private:

public:
    Hanning(size_t N);
    Hanning();
};