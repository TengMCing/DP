cmake_minimum_required(VERSION 3.22)
project(vec_lang_2 C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_VERBOSE_MAKEFILE ON)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra")

add_executable(vec_lang_2 main.c vector.h args.h class.h error.h error_check.h generic.h vector_method.h vector_method.c utilities.h vector_info.c generic.c)
