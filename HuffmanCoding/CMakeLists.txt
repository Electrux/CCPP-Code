cmake_minimum_required(VERSION 3.8)
project(HuffmanCoding)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES src/main.cpp include/HuffmanCode.hpp)
add_executable(HuffmanCoding ${SOURCE_FILES})