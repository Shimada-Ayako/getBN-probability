cmake_minimum_required(VERSION 3.29)
project(main CXX)
add_subdirectory(src)
add_subdirectory(bin)
# set compiler version
add_definitions( -std=c++20 -Wall )
set(CMAKE_CXX_COMPILER clang++)







