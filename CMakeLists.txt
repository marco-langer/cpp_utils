cmake_minimum_required(VERSION 3.18.4)

project(CPP_UTILS LANGUAGES CXX)

include(GNUInstallDirs)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Check compiler requirements
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS "10.2.1")
        message(FATAL_ERROR "Insufficient gcc version: 10.2.1 required")
    endif()
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "CLANG")
    if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS "11.0.1")
        message(FATAL_ERROR "Insufficient clang version: 11.0.1 required")
    endif()
endif()

option(WITH_TESTS "Enable building of tests" ON)
if(WITH_TESTS)
    message(STATUS "Building tests: Yes")
    enable_testing()
else()
    message(STATUS "Building tests: No")
endif()

option(WITH_ASAN "Enable address sanitizer for tests" OFF)
if(WITH_ASAN)
    message(STATUS "Asan enabled")
else()
    message(STATUS "Asan disabled")
endif()

option(WITH_UBSAN "Enable undefined behaviour sanitizer" OFF)
if(WITH_UBSAN)
    message(STATUS "UBsan enabled")
else()
    message(STATUS "UBsan disabled")
endif()

# Set Version
set(CPP_UTILS_VERSION_MAJOR "0")
set(CPP_UTILS_VERSION_MINOR "0")
set(CPP_UTILS_VERSION_PATCH "1")
set(CPP_UTILS_VERSION "${CPP_UTILS_VERSION_MAJOR}.${CPP_UTILS_VERSION_MINOR}.${CPP_UTILS_VERSION_PATCH}")

# Build type
set(DEFAULT_BUILD_TYPE "Debug")
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE "${DEFAULT_BUILD_TYPE}")
endif()
message(STATUS "Setting up build for stdbp v${STDBP_VERSION} (${CMAKE_BUILD_TYPE})")

# Compiler warnings
macro(add_gcc_compiler_cxxflags FLAGS)
    if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_COMPILER_IS_CLANGXX)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${FLAGS}")
    endif()
endmacro(add_gcc_compiler_cxxflags)

add_gcc_compiler_cxxflags(
    "-Wall -Wextra -Wpedantic -Wundef -Wpointer-arith -Wno-long-long "
    "-Wshadow -Wnon-virtual-dtor -Wold-style-cast -Wcast-align -Wunused "
    "-Woverload-virtual -Wconversion -Wsign-conversion -Wdouble-promotion "
    "-Wformat=2 -Wduplicated-cond -Wduplicated-branches "
    "-Wlogical-op -Wuseless-cast -Wlifetime")

if (WITH_TESTS)
  add_subdirectory(test)
endif()
