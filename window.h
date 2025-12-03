#pragma once
#include <iostream>
#include <string>
#include <vector>

class Window{
private:
protected:
    std::vector<double> coeffs_ = {};
    std::string name_ = "";
public:
    Window(std:: string n) : name_(n) {}

    void printCoeffs() const{
        std::cout << "all " << name_ << " window coefficients:" << std::endl;
        std::cout << "["; 
        for(int i = 0; i < coeffs_.size(); i++){
            std::cout << coeffs_[i] << ",";
        }
        std::cout << "]" << std::endl;   
    }

    std::vector<double> getCoeffs() const{
        return coeffs_;
    }

    std::string getName() const{
        return name_;
    }

    size_t size() const{
        return coeffs_.size();
    }

    virtual ~Window(){};
};