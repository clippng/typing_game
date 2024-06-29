cmake_minimum_required(VERSION 3.10)

add_executable(Typer main.cpp)

target_link_libraries(Typer PUBLIC game renderer tools SDL2)

