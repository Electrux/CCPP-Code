cmake_minimum_required(VERSION 3.8)
project(Graph)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES src/main.cpp include/Graph.hpp)
add_executable(Graph ${SOURCE_FILES})