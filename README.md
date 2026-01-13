# DigitalFilters Library

A C++ library for the design and analysis of digital signal filters (FIR, IIR). It enables easy creation of low-pass and high-pass filters, application of time windows, and generation of time response and frequency response (Bode) plots.

The library was created by Jakub Kubuszek.

# About the project
The library is my final project for the "Object-oriented programming languages" course at AGH in Cracow.

## Features

* **FIR Filters:** Design using the window method (LowPass, HighPass), support for custom coefficients.
* **IIR Filters:** Support for custom coefficients (feedforward/feedback).
* **Time Windows:** Available Hamming and Hanning windows.
* **Analysis:** Generation of data for Bode plots (magnitude and phase).
* **Visualization:** Built-in plotting functions (requires Gnuplot).

## Requirements

To build and use the library, you need:

* A C++ compiler supporting the **C++17** standard.
* **CMake** version 3.14 or newer.
* **Gnuplot** (installed on the system) – required for generating PDF plots.

### Gnuplot Installation (Linux/Ubuntu)

sudo apt update
sudo apt install gnuplot    

### Building and installation

The project uses CMake. To build the library follow these steps:

1.  Create build directory

    mkdir build && cd build
    
2.  Configure project

    cmake ..
    
3.  Build the library

    make

4.  (optional) install the library 

    sudo make install

## Project structure

* `include/DigitalFilters/` - library header files
* `src/` - library source files
* `examples/` - use examples
* `libs/` - external libraries (sciplot)
* `docs/` - doxygen documentation 

## Documentation

    link to doxygen-generated documentation on github pages:
    https://jkubuszek.github.io/Digital-filters/ 

## Licence

This project uses MIT sharing license. More in `LICENSE`