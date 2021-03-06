cmake_minimum_required(VERSION 2.8)

project(Feral C CXX)

set(CMAKE_CXX_STANDARD 11)
if(CMAKE_VERSION VERSION_LESS "3.1")
	add_compile_options(-std=c++11)
endif()

# add cmake_modules path
list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/third_party/cmake_modules")

set(FERAL_VERSION_MAJOR 0)
set(FERAL_VERSION_MINOR 0)
set(FERAL_VERSION_PATCH 1)

execute_process(COMMAND date "+%a %b %d, %Y at %H:%M:%S" OUTPUT_VARIABLE BUILD_DATE OUTPUT_STRIP_TRAILING_WHITESPACE)

set(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE)
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
set(CMAKE_MACOSX_RPATH TRUE)

include(CheckCXXCompilerFlag)

set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
if(CMAKE_USE_PTHREADS_INIT)
	message("-- Using thread flags: -pthread")
	set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -pthread")
	set(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} -pthread")
else()
	message("-- Using thread flags: ${CMAKE_THREAD_LIBS_INIT}")
	set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${CMAKE_THREAD_LIBS_INIT}")
	set(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${CMAKE_THREAD_LIBS_INIT}")
endif()

# For libGMP on macOS and BSD
if(APPLE OR ${CMAKE_SYSTEM_NAME} MATCHES ".*BSD.*")
	include_directories(/usr/local/include)
	link_directories(/usr/local/lib)
endif()

if(WIN32)
	error("Project not supported on Windows yet")
endif()

find_program(CCACHE_PROGRAM ccache)
if(CCACHE_PROGRAM)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "${CCACHE_PROGRAM}")
endif()

if(${CMAKE_SYSTEM_NAME} MATCHES ".*BSD.*")
	add_definitions(-D_WITH_GETLINE)
endif()

if(DEFINED ENV{DEBUG})
	add_definitions(-DDEBUG_MODE)
	message("-- Running in debug mode")
else()
	if(NOT DEFINED ENV{SKIP_LTO})
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -flto")
	endif()
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")
endif()

check_cxx_compiler_flag(-march=native COMPILER_SUPPORTS_MARCH_NATIVE)
if(COMPILER_SUPPORTS_MARCH_NATIVE)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=native")
endif()

if(DEFINED ENV{PREFIX_DIR} AND NOT "$ENV{PREFIX_DIR}" STREQUAL "")
	set(CMAKE_INSTALL_PREFIX "$ENV{PREFIX_DIR}")
else()
	set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}")
endif()
add_definitions(-DBUILD_PREFIX_DIR=${CMAKE_INSTALL_PREFIX})
set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib/feral")
message("-- Using PREFIX = ${CMAKE_INSTALL_PREFIX}")

# Finally! The sources!!!!!

# Set Config.hpp.in template
configure_file("${PROJECT_SOURCE_DIR}/src/Config.hpp.in" "${PROJECT_SOURCE_DIR}/src/Config.hpp" @ONLY)

# Feral Core
file(GLOB_RECURSE INCS RELATIVE "${PROJECT_SOURCE_DIR}" "src/*.hpp")
file(GLOB_RECURSE SRCS RELATIVE "${PROJECT_SOURCE_DIR}" "src/*.cpp")
list(REMOVE_ITEM SRCS "src/Main.cpp")

add_library(feral-lib SHARED ${SRCS} ${INCS})
target_link_libraries(feral-lib ${CMAKE_DL_LIBS})
set_target_properties(feral-lib
    PROPERTIES
    OUTPUT_NAME feral
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib/feral"
    INSTALL_RPATH_USE_LINK_PATH TRUE
)
install(TARGETS feral-lib
	LIBRARY
	  DESTINATION lib/feral
	  COMPONENT Libraries
	PUBLIC_HEADER
	  DESTINATION include/feral
)

add_executable(feral-bin "${PROJECT_SOURCE_DIR}/src/Main.cpp")
target_link_libraries(feral-bin feral-lib)
set_target_properties(feral-bin
	PROPERTIES
	OUTPUT_NAME feral
	RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
	INSTALL_RPATH_USE_LINK_PATH TRUE
)
install(TARGETS feral-bin
	RUNTIME
	  DESTINATION bin
	  COMPONENT Binaries
)
