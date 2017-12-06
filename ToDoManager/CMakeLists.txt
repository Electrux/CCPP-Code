cmake_minimum_required(VERSION 3.2)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
project(ToDoManager)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build)

set(CMAKE_CXX_STANDARD 14)

file(GLOB SOURCE_FILES src/*.cpp)
add_executable(ToDoManager ${SOURCE_FILES})

