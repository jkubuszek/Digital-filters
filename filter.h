#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "window.h"

class Filter{
private:
    
protected:
    std::string name_ = "";

public:
    Filter(std::string n) : name_(n) {}

    virtual std::vector<double> getCoeffs() const = 0;

    virtual void printCoeffs() const = 0;

    virtual std::vector<double> response(const std::vector<double> &x) = 0;

    virtual std::vector<double> windowed_response(const std::vector<double> &x, const Window &win) = 0;

    std::string getName() const{
        return name_;
    }
    void print_name() const{
        std::cout << "filter name: " << name_ << std::endl; 
    }
    virtual ~Filter(){}
};