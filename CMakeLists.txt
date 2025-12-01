cmake_minimum_required(VERSION 3.10)

project(Project C)

set(CMAKE_C_STANDARD 11)

add_executable(app 
    src/main.c
    src/DataStructures/DynamicArray.c
    src/DataStructures/LinkedList.c
    src/DataStructures/Stack.c
    src/DataStructures/Structures.c
    src/Days/Day1.c
)

target_include_directories(app PRIVATE ${CMAKE_SOURCE_DIR}/src/DataStructures)
target_include_directories(app PRIVATE ${CMAKE_SOURCE_DIR}/src/Days)
target_include_directories(app PRIVATE ${CMAKE_SOURCE_DIR}/src)