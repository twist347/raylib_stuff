cmake_minimum_required(VERSION 3.10)

project(raylib_stuff)

set(CMAKE_C_STANDARD 11)

set(RAYLIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/external/raylib-5.5_linux_amd64)
set(GAMES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/games)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_compile_options(-Wall -Wextra -pedantic)

include_directories(${RAYLIB_DIR}/include)
link_directories(${RAYLIB_DIR}/lib)

add_subdirectory(${GAMES_DIR}/snake)
add_subdirectory(${GAMES_DIR}/arkanoid)
add_subdirectory(${GAMES_DIR}/platformer)

add_subdirectory(${GAMES_DIR}/ecs/ping_pong_ecs)
add_subdirectory(${GAMES_DIR}/ecs/tds_ecs)