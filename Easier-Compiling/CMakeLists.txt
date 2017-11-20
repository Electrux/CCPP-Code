cmake_minimum_required(VERSION 3.8)
project(EasierCompiling)

set(CMAKE_C_STANDARD 11)

set(SOURCE_FILES src/main.c include/funcs.h)
add_executable(EasierCompiling ${SOURCE_FILES})