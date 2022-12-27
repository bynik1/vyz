add_executable(string main.cpp)

add_compile_options(-fsanitize=address)
add_compile_options(-Wall -Wextra -std=c++20)

include_directories(../libstring)
target_link_libraries(string libstring)
