cmake_minimum_required(VERSION 3.2)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
project(Process_Scheduling)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build)

set(CMAKE_C_STANDARD 11)

set(SOURCE_FILES ./src/3_priority.c)
add_executable(Process_Scheduling ${SOURCE_FILES})

