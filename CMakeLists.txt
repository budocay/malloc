cmake_minimum_required(VERSION 2.8)
project(malloc)

include_directories(my_libc/include)

set(CMAKE_C_FLAGS  "${CMAKE_C_FLAGS} -Wall -Wextra -Werror -fPIC -I./src_alexis/include")
set(CC "clang")

set(SOURCE_FILES src_alexis/malloc.c src_alexis/management_block.c src_alexis/include/malloc.h src_alexis/calloc.c)
# add_executable(malloc ${SOURCE_FILES})
# target_link_libraries(malloc)
add_library(malloc SHARED ${SOURCE_FILES})