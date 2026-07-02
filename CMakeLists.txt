cmake_minimum_required(VERSION 4.2)
project(KNearestNeighbors)

set(CMAKE_CXX_STANDARD 23)

add_executable(KNearestNeighbors main.cpp
        color.h
        colors.cpp
        split.cpp)
