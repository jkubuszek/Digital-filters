#include "DigitalFilters/window.hpp"
#include <iostream>

namespace JK{
    Window::Window(std:: string n) : name(n) {}
    Window::Window(){
        name = "";
        coeffs = {0.0};
    }

    void Window::printCoeffs() const{
        std::cout << "all " << name << " window coefficients:" << std::endl;
        std::cout << "["; 
        for(int i = 0; i < coeffs.size(); i++){
            std::cout << coeffs[i] << ",";
        }
        std::cout << "]" << std::endl;   
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