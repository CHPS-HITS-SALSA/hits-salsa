# Support a range of CMake versions, starting form C++20 support
cmake_minimum_required(VERSION 3.12...3.24)

project(hits-salsa
  VERSION 0.1.0
  DESCRIPTION "Sparse HITS and SALSA implementations for parallel systems"
  LANGUAGES CXX)

find_package(nlohmann_json 3.2.0 REQUIRED)

add_executable(hits src/hits/main.cpp)
target_link_libraries(hits PRIVATE nlohmann_json::nlohmann_json)
target_compile_features(hits PUBLIC cxx_std_17)

add_executable(salsa src/salsa/main.cpp)
target_compile_features(salsa PUBLIC cxx_std_17)
