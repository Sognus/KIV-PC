cmake_minimum_required(VERSION 3.10)
project(KIV_PC C)

set(CMAKE_C_STANDARD 90)

add_executable(sistem.exe main.c context.c context.h main.h config.h string_helper.c string_helper.h)