cmake_minimum_required(VERSION 3.20)


project(CPlusPlusBestC LANGUAGES CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20")

add_executable(main main.cpp)