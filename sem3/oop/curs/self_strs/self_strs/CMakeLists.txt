cmake_minimum_required(VERSION 2.8.12)

project(lib)

add_compile_options(-Wall -Wextra -std=c++20)

add_subdirectory(src/libstring)
add_subdirectory(src/string)

# message("output:\n")
