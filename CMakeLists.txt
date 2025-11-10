cmake_minimum_required(VERSION 3.31)
project(R5.B.04 C)

set(CMAKE_C_STANDARD 23)

add_subdirectory(tp0.1)
add_subdirectory(tp1)
add_subdirectory(tp2)
add_subdirectory(tp_threads)
add_executable(tp3_synthese tp3/synthese.c)
