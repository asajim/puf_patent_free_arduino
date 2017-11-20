cmake_minimum_required(VERSION 3.8)
project(SerialServer)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main3.cpp Tools.cpp BCH.cpp)
add_executable(SerialServer ${SOURCE_FILES})