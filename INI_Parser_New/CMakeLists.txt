cmake_minimum_required(VERSION 3.8)
project(INI_Parser)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES src/main.cpp include/Section.hpp src/Section.cpp include/INI_Parser.hpp src/INI_Parser.cpp include/DataVars.hpp)
add_executable(INI_Parser ${SOURCE_FILES})