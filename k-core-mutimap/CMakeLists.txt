cmake_minimum_required(VERSION 3.17)
project(k_core_mutimap)

set(CMAKE_CXX_STANDARD 14)

add_executable(k_core_mutimap main.cpp Graph.cpp Graph.h subGraph.cpp subGraph.h Store.h Person.h)