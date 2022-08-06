cmake_minimum_required(VERSION 3.10)
set(CMAKE_C_STANDARD 23)
project(zux C ASM)

add_subdirectory(kern)
add_subdirectory(loader)
