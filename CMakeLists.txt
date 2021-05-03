cmake_minimum_required(VERSION 2.6)
SET(CMAKE_CXX_FLAGS " -msse2 -mssse3 -std=c++11 -fexpensive-optimizations -fopenmp ")
SET(CMAKE_C_FLAGS " -msse2 -mssse3 -std=c++11 -fexpensive-optimizations -fopenmp ")

add_subdirectory(IsingMagnet)
