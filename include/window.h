#pragma once
#include <iostream>
#include <string>
#include <vector>

class Window{
private:
protected:
    std::vector<double> coeffs = {};
    std::string name = "";
public:
    Window(std:: string n) : name(n) {}
    Window(){
        name = "";
        coeffs = {0.0};
    }

    void printCoeffs() const{
        std::cout << "all " << name << " window coefficients:" << std::endl;
        std::cout << "["; 
        for(int i = 0; i < coeffs.size(); i++){
            std::cout << coeffs[i] << ",";
        }
        std::cout << "]" << std::endl;   
    }

    std::vector<double> getCoeffs() const{
        return coeffs;
    }

    std::string getName() const{
        return name;
    }
    void setName(std::string n){
        name = n;
    }

    size_t size() const{
        return coeffs.size();
    }

    virtual ~Window(){};
};