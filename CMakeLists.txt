cmake_minimum_required(VERSION 3.29)
project(ArrayList C)

set(CMAKE_C_STANDARD 23)

# Add the static library
add_library(ArrayList STATIC ArrayList.c)

# Add the executable
add_executable(main main.c)

# Link the ArrayList library to the main executable
target_link_libraries(main ArrayList)