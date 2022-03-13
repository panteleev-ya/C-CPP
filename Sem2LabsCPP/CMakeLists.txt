cmake_minimum_required(VERSION 3.21)
project(clion)

set(CMAKE_CXX_STANDARD 20)

add_executable(clion main.cpp Point.h BrokenLine.h FinalBrokenLine.h Polygon.h Triangle.h Trapezoid.h RegularPolygon.h Polynomial.h)
