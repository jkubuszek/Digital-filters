cmake_minimum_required(VERSION 3.12)
project(DigitalFiltersProject VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)
include_directories(libs)

add_library(DigitalFiltersLib
    src/filter.cpp
    src/fir.cpp
    src/iir.cpp
    src/window.cpp
    src/hamming.cpp 
    src/hanning.cpp
    src/plots.cpp
)

add_executable(test main.cpp)
target_link_libraries(test PRIVATE DigitalFiltersLib)


if(UNIX)
    target_link_libraries(test PRIVATE m)
endif()