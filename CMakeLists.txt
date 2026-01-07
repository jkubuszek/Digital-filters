# initial configuration
cmake_minimum_required(VERSION 3.14) 
project(DigitalFilters VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# library definiton
add_library(DigitalFiltersLib STATIC
    src/filter.cpp
    src/fir.cpp
    src/iir.cpp
    src/window.cpp
    src/hamming.cpp 
    src/hanning.cpp
    src/plots.cpp
)

# hiding the plots implementation (sciplot)
target_include_directories(DigitalFiltersLib PRIVATE libs) 

# client-side interfaces, so the library "knows where to look" for header files
target_include_directories(DigitalFiltersLib PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

# standard installation 
include(GNUInstallDirs)
install(TARGETS DigitalFiltersLib
    EXPORT DigitalFiltersTargets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

# exporting the library configuration, needed for find_package to work
install(EXPORT DigitalFiltersTargets
    FILE DigitalFiltersConfig.cmake
    NAMESPACE JK::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/DigitalFilters
)

# building examples
option(BUILD_EXAMPLES "Build example applications" ON)
if(BUILD_EXAMPLES)
    add_executable(DigitalFiltersExample examples/main.cpp)
    target_link_libraries(DigitalFiltersExample PRIVATE DigitalFiltersLib)
    target_include_directories(DigitalFiltersExample PRIVATE libs)
    # linking the math library for unix
    if(UNIX)
        target_link_libraries(DigitalFiltersExample PRIVATE m)
    endif()
endif()