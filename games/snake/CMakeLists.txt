cmake_minimum_required(VERSION 3.10)

set(T snake)

project(${T})

include_directories(include)

add_executable(${T}
    main.c
    src/config.c
    src/game.c
    src/markings.c
    src/hud.c
    src/snake.c
    src/food.c
)

target_link_libraries(${T} raylib m)