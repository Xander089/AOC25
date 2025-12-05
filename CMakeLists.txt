cmake_minimum_required(VERSION 3.10)

project(Project C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_BUILD_TYPE Debug)
add_compile_options(-g -O0)

add_executable(app 
    src/main.c
    src/DataStructures/DynamicArray.c
    src/DataStructures/LinkedList.c
    src/DataStructures/Stack.c
    src/DataStructures/Structures.c
    src/Days/Day1.c
    src/Days/Day2.c
    src/Days/Day3.c
    src/Days/Day4.c
    src/Days/Day5.c
)

target_include_directories(app PRIVATE ${CMAKE_SOURCE_DIR}/src/DataStructures)
target_include_directories(app PRIVATE ${CMAKE_SOURCE_DIR}/src/Days)
target_include_directories(app PRIVATE ${CMAKE_SOURCE_DIR}/src)