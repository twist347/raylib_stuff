set(T platformer)

project(${T})

set(ASSETS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/assets)

add_executable(${T}
        ${CMAKE_CURRENT_SOURCE_DIR}/main.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/screen_settings.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/platform.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/game.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/player.c
)

target_include_directories(${T} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(${T} PRIVATE raylib m)

#target_compile_definitions(${T} PRIVATE ASSETS_DIR=\"${ASSETS_DIR}\")