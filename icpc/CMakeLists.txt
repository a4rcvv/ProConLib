cmake_minimum_required(VERSION 3.15)
project(icpc)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-g -O0 -std=gnu++14 -static -Wextra")

add_executable(a a.cpp)
add_executable(b b.cpp)
#add_executable(c c.cpp)
#...
