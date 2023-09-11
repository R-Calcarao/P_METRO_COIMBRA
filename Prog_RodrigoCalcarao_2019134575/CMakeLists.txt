cmake_minimum_required(VERSION 3.25)
project(TP C)

set(CMAKE_C_STANDARD 99)

add_executable(TP main.c func_aux.c func_aux.h struct.h struct.c)
