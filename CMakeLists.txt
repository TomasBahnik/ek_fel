cmake_minimum_required(VERSION 3.16)

#project(cpp-lab01)
#set(CMAKE_CXX_STANDARD 14)
#add_executable(cpp_labs01
#        C++/labs/01/1.cpp)

project(hw01)
set(CMAKE_CXX_STANDARD 14)
add_executable(hw_01
        C++/HWs/hw01/main.cpp
        C++/HWs/hw01/main.hpp
        C++/HWs/hw01/parse.hpp
        C++/HWs/hw01/parse.cpp)

project(hw02)
set(CMAKE_CXX_STANDARD 14)
add_executable(hw_02
        C++/HWs/hw02/main.cpp
        C++/HWs/hw02/doprava.cpp
        C++/HWs/hw02/doprava.hpp)

project(hw03)
set(CMAKE_CXX_STANDARD 14)
add_executable(hw_03
        C++/HWs/hw03/template/main.cpp
        C++/HWs/hw03/template/main.hpp)

project(hw04)
set(CMAKE_CXX_STANDARD 14)
add_executable(hw_04
        C++/HWs/hw04/main.cpp
        C++/HWs/hw04/matrix.cpp
        C++/HWs/hw04/matrix.hpp)