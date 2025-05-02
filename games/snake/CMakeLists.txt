set(T snake)

project(${T})

set(ASSETS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/assets)

add_executable(
    ${T}
    ${CMAKE_CURRENT_SOURCE_DIR}/main.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/screen_settings.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/game.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/markings.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/hud.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/audio.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/utils.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/collisions.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/screen.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/snake.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/food.c
)

target_include_directories(snake PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(snake PRIVATE raylib m)

target_compile_definitions(snake PRIVATE ASSETS_DIR=\"${ASSETS_DIR}\")
