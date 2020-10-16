cmake_minimum_required(VERSION 3.9.2)
project(filter C)

set(CMAKE_C_STANDARD 99)

include_directories(inc)
add_executable(filter src/main.c inc/str.h src/str.c inc/vec.h src/vec.c inc/filter.h src/filter.c)

add_subdirectory(unit_tests)