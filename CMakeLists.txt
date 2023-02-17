# Support a range of CMake versions, starting form C++20 support
cmake_minimum_required(VERSION 3.12...3.24)

project(hits-salsa
  VERSION 0.1.0
  DESCRIPTION "Sparse HITS and SALSA implementations for parallel systems"
  LANGUAGES CXX)

find_package(nlohmann_json 3.2.0 REQUIRED)

set(CMAKE_CXX_STANDARD 17)

# Objects
add_library(csmat OBJECT include/csmat.hpp)
target_include_directories(csmat PRIVATE include)

add_library(blas OBJECT include/blas.hpp)
target_include_directories(blas PRIVATE include)

add_library(hits OBJECT include/algorithms/hits.hpp)
target_include_directories(hits PRIVATE include)

add_library(utils OBJECT src/utils.cpp include/utils.hpp)
target_include_directories(utils PRIVATE include)

# Tests
add_executable(test-csmat test/csmat.cpp)
target_include_directories(test-csmat PRIVATE include)
target_link_libraries(test-csmat PRIVATE csmat)

add_executable(test-blas test/blas.cpp)
target_include_directories(test-blas PRIVATE include)
target_link_libraries(test-blas PRIVATE csmat blas)

add_executable(test-json test/json.cpp)
target_include_directories(test-json PRIVATE include)
target_link_libraries(test-json PRIVATE utils)

add_executable(test-hits test/hits.cpp)
target_include_directories(test-hits PRIVATE include)
target_link_libraries(test-hits PRIVATE utils)
