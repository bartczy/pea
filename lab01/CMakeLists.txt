cmake_minimum_required(VERSION 4.1)
project(lab01)

set(CMAKE_CXX_STANDARD 20)

add_executable(lab01 main.cpp
        TSP.h
        TSP.cpp
        Timer.h)
