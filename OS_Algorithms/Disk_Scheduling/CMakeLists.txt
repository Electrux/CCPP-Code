cmake_minimum_required(VERSION 3.2)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
project(Disk_Scheduling)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build)

set(CMAKE_C_STANDARD 11)

set(SOURCE_FILES ./src/10_scan.c)
add_executable(Disk_Scheduling ${SOURCE_FILES})

