#include "DigitalFilters/window.hpp"
#include <iostream>

namespace JK{
    Window::Window(std:: string n) : name(n) {}
    Window::Window(){
        name = "";
        coeffs = {0.0};
    }

    bool Window::operator==(const Window& other) const {
        return this->coeffs == other.coeffs; 
    }

    bool Window::operator!=(const Window& other) const {
        return this->coeffs != other.coeffs; 
    }

    std::ostream& operator<<(std::ostream& os, const Window& w) {
        os << "Window Name: " << w.name << "\n";
        os << "Coefficients: [";
        for (size_t i = 0; i < w.coeffs.size(); i++) {
            os << w.coeffs[i] << (i < w.coeffs.size() - 1 ? ", " : "");
        }
        os << "]";
        return os;
    }


    std::vector<double> Window::getCoeffs() const{
        return coeffs;
    }

    std::string Window::getName() const{
        return name;
    }
    void Window::setName(std::string n){
        name = n;
    }

    size_t Window::size() const{
        return coeffs.size();
    }

    Window::~Window(){};
}