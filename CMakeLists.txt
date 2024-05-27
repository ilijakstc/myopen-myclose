cmake_minimum_required(VERSION 3.20)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)

project(Myopen_Myclose)

set(SOURCE_FILES src/main.c src/mypopen.c src/mypclose.c)

add_executable(Myopne_Myclose ${SOURCE_FILES})