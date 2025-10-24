cmake_minimum_required(VERSION 3.10)
project(peterson_r_min_in_cols)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Main executable
add_executable(peterson_r_min_in_cols src/main.cpp src/peterson_r_min_in_cols_seq.cpp)

# Functional tests
add_executable(seq_func_tests func_tests/func_tests.cpp src/peterson_r_min_in_cols_seq.cpp)

# Performance tests
add_executable(seq_perf_tests perf_tests/perf_tests.cpp src/peterson_r_min_in_cols_seq.cpp)

install(TARGETS peterson_r_min_in_cols seq_func_tests seq_perf_tests DESTINATION bin)
