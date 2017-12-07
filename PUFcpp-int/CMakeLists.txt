cmake_minimum_required(VERSION 3.8)
project(PUFcpp_int)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main2.cpp Tools.cpp BCH.cpp)
add_executable(PUFcpp_int ${SOURCE_FILES})