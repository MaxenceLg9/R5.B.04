cmake_minimum_required(VERSION 4.1)
project(tp2 C)

set(CMAKE_C_STANDARD 23)

add_executable(tp2_ex1a ex1a.c
        ex2b.c
        ex3.c)
target_link_libraries(tp2_ex1a m)

add_executable(tp2_ex1b ex1b.c)
target_link_libraries(tp2_ex1b m)

add_executable(tp2_ex1c ex1c.c)
target_link_libraries(tp2_ex1c m)

add_executable(tp2_ex2a ex2a.c)

add_executable(tp2_ex2b ex2b.c)

add_executable(tp2_ex3 ex3.c)
