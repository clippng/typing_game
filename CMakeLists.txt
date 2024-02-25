cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 20)

project(TypingGame)

include_directories(libs)

add_executable(
TypingGame

typing_game/main.cpp
typing_game/game.cpp
typing_game/gui.cpp
typing_game/paragraph.cpp

typing_game/main.hpp
typing_game/game.hpp
typing_game/gui.hpp
typing_game/paragraph.hpp

imgui/imgui.h
)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})
target_link_libraries(TypingGame ${CURSES_LIBRARIES})