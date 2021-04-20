cmake_minimum_required(VERSION 3.17)
project(nhf2streams)

set(CMAKE_CXX_STANDARD 14)

add_executable(nhf2streams main.cpp stream.cpp stream.h era.cpp era.h linkedlist.h)