set(T arkanoid)

project(${T})

set(ASSETS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/assets)

add_executable(${T}
    ${CMAKE_CURRENT_SOURCE_DIR}/main.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/screen_settings.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/game.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/paddle.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/ball.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/brick.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/collisions.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/hud.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/ui.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/map_generator.c
)

target_include_directories(${T} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(${T} PRIVATE raylib m)

target_compile_definitions(${T} PRIVATE ASSETS_DIR=\"${ASSETS_DIR}\")