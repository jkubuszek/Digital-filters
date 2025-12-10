cmake_minimum_required(VERSION 3.10)


project(DigitalFilters VERSION 1.0 LANGUAGES CXX)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON) 


# if(MSVC)
#     add_compile_options(/W4)
# else()
#     add_compile_options(-Wall -Wextra)
# endif()


add_executable(test src/main.cpp)

target_include_directories(test PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/libs
)


if(UNIX)
    target_link_libraries(test PRIVATE m)
endif()