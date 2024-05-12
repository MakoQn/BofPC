cmake_minimum_required(VERSION 3.26)
project(C23Exe C)

set(CMAKE_C_STANDARD 23)

add_executable(C23Exe main.c)

add_subdirectory(libs)
target_link_libraries(C23Exe data_structures)
target_link_libraries(C23Exe algorithms)
