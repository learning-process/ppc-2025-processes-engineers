cmake_minimum_required(VERSION 3.10)
project(peterson_r_min_in_cols)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(peterson_r_min_in_cols main.cpp)

install(TARGETS peterson_r_min_in_cols DESTINATION bin)
