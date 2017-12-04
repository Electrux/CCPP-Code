cmake_minimum_required(VERSION 3.8)
project(HashTableImplementation)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES src/main.cpp include/Table.hpp include/HashKey.hpp include/HashTable.hpp include/Stack.hpp include/Constants.hpp include/TemplateDefs.hpp)
add_executable(HashTableImplementation ${SOURCE_FILES})
