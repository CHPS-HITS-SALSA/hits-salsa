# Support a range of CMake versions, starting form C++20 support
cmake_minimum_required(VERSION 3.12...3.24)

project(hits-salsa
  VERSION 0.1.0
  DESCRIPTION "Sparse HITS and SALSA implementations for parallel systems"
  LANGUAGES CXX)

find_package(OpenMP REQUIRED)
find_package(nlohmann_json 3.2.0 REQUIRED)

set(CMAKE_CXX_STANDARD 17)

# Objects
add_library(csmat OBJECT include/csmat.hpp)
target_link_libraries(csmat PUBLIC OpenMP::OpenMP_CXX)
target_include_directories(csmat PUBLIC include)

add_library(blas OBJECT include/blas.hpp)
target_link_libraries(csmat PUBLIC OpenMP::OpenMP_CXX)
target_include_directories(blas PUBLIC include)

add_library(hits OBJECT include/algorithms/hits.hpp)
target_include_directories(hits PUBLIC include)

add_library(utils OBJECT src/utils.cpp include/utils.hpp)
target_include_directories(utils PUBLIC include)

# Tests
add_executable(test-csmat test/csmat.cpp)
target_include_directories(test-csmat PUBLIC include)
target_link_libraries(test-csmat PUBLIC csmat)

add_executable(test-blas test/blas.cpp)
target_include_directories(test-blas PUBLIC include)
target_link_libraries(test-blas PUBLIC csmat blas)

add_executable(test-json test/json.cpp)
target_include_directories(test-json PUBLIC include)
target_link_libraries(test-json PUBLIC utils)
