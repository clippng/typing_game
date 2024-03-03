cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 20)

project(TypingGame VERSION 0.1.3)

add_subdirectory(typing_game)

find_package(Vulkan REQUIRED)
find_package(SDL2 REQUIRED)
