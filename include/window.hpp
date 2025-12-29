#pragma once
#include <string>
#include <vector>

class Window{
protected:

    std::vector<double> coeffs = {};
    std::string name = "";
    
public:

    Window(std:: string n);
    Window();

    void printCoeffs() const;

    std::vector<double> getCoeffs() const;

    std::string getName() const;

    void setName(std::string n);

    size_t size() const;

    virtual ~Window();
};