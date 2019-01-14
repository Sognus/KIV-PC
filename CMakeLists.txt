cmake_minimum_required(VERSION 3.10)
project(KIV_PC C)

set(CMAKE_C_STANDARD 90)
set(CMAKE_C_FLAGS "-Wall -ansi -pedantic")

add_executable(sistem.exe main.c context.c context.h main.h config.h trie.c trie.h learning_mode.c learning_mode.h processing_mode.c processing_mode.h string_helper.c string_helper.h lcs.c lcs.h linked_list.c linked_list.h file_helper.c file_helper.h)