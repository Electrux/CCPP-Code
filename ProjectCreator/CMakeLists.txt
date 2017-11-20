cmake_minimum_required(VERSION 3.8)
project(ProjectCreator)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES src/main.cpp include/ToVector.hpp include/Data.hpp include/FlagFunctions.hpp include/CMakeGenerator.hpp include/FindSFML.hpp include/DirFileFunctions.hpp include/FindSDL2.hpp include/FindSDL2_Image.hpp include/FindSDL2_TTF.hpp include/SFMLDefaultMain.hpp include/SDL2DefaultMain.hpp)
add_executable(ProjectCreator ${SOURCE_FILES})
