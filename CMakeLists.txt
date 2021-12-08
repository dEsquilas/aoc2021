cmake_minimum_required(VERSION 3.14)
project(aoc_2021)

set(CMAKE_CXX_STANDARD 17)

set(Sources day-01/main.cpp)
add_executable(day-01 ${Sources})

set(Sources day-02/main.cpp)
add_executable(day-02 ${Sources})

set(Sources day-03/main.cpp)
add_executable(day-03 ${Sources})

set(Sources day-04/main.cpp)
add_executable(day-04 ${Sources})

set(Sources day-05/main.cpp)
add_executable(day-05 ${Sources})

set(Sources6 day-06/main.cpp)
add_executable(day-06 ${Sources6})

set(Sources7 day-07/main.cpp)
add_executable(day-07 ${Sources6})

set(Sources8 day-08/main.cpp)
add_executable(day-08 ${Sources6})