cmake_minimum_required(VERSION 3.3)
project(malloc)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -fPIC -shared -o malloc.so")

set(SOURCE_FILES malloc.c malloc_tp.h)
add_executable(malloc ${SOURCE_FILES})