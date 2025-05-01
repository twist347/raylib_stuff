cmake_minimum_required(VERSION 3.10)

set(T snake)

project(${T})

set(ASSETS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/assets)

include_directories(include)

add_executable(${T}
    main.c
    src/screen_settings.c
    src/game.c
    src/markings.c
    src/hud.c
    src/audio.c
    src/utils.c
    src/collisions.c
    src/screen.c
    src/snake.c
    src/food.c
)

target_link_libraries(${T} raylib m)

target_compile_definitions(${T} PRIVATE ASSETS_DIR=\"${ASSETS_DIR}\")
