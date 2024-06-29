cmake_minimum_required(VERSION 3.10)

add_library(tools STATIC paragraph.cpp event_handler.cpp)

target_include_directories(tools PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# target_link_libraries(world PUBLIC)

