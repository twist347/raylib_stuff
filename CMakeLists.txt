cmake_minimum_required(VERSION 3.10)

project(raylib_stuff)

set(RAYLIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/external/raylib-5.5_linux_amd64)

set(LESSONS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lessons)
set(DEMOS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/demos)
set(GAMES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/games)

add_compile_options(-Wall -Wextra -pedantic)

include_directories(${RAYLIB_DIR}/include)
link_directories(${RAYLIB_DIR}/lib)

add_subdirectory(${LESSONS_DIR}/01_window)
add_subdirectory(${LESSONS_DIR}/02_primitives)

add_subdirectory(${DEMOS_DIR}/01_window)
add_subdirectory(${DEMOS_DIR}/02_primitives)

add_subdirectory(${GAMES_DIR})

add_subdirectory(test_stuff)
