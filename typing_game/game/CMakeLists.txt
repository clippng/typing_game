cmake_minimum_required(VERSION 3.10)

add_library(game STATIC game.cpp)

target_include_directories(game PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(game PUBLIC renderer tools SDL2)

