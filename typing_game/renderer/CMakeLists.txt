cmake_minimum_required(VERSION 3.10)

add_library(renderer STATIC renderer.cpp)

target_include_directories(renderer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(renderer PRIVATE SDL2 SDL2_ttf)

# target_link_libraries(render PUBLIC )

