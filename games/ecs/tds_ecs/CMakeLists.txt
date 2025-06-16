set(T tds_ecs)

project(${T})

#set(ASSETS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/assets)

add_executable(${T}
        ${CMAKE_CURRENT_SOURCE_DIR}/main.c
#        ${CMAKE_CURRENT_SOURCE_DIR}/src/game.c
#        ${CMAKE_CURRENT_SOURCE_DIR}/src/world.c
#        ${CMAKE_CURRENT_SOURCE_DIR}/src/systems/system_collisions.c
#        ${CMAKE_CURRENT_SOURCE_DIR}/src/systems/system_input.c
#        ${CMAKE_CURRENT_SOURCE_DIR}/src/systems/system_music.c
#        ${CMAKE_CURRENT_SOURCE_DIR}/src/systems/system_render.c
#        ${CMAKE_CURRENT_SOURCE_DIR}/src/systems/system_score.c
#        ${CMAKE_CURRENT_SOURCE_DIR}/src/systems/system_sound.c
#        ${CMAKE_CURRENT_SOURCE_DIR}/src/systems/system_transform.c
)

target_include_directories(${T} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(${T} PRIVATE raylib m)

#target_compile_definitions(${T} PRIVATE ASSETS_DIR=\"${ASSETS_DIR}\")
