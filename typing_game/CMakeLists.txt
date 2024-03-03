cmake_minimum_required(VERSION 3.10)

add_executable(typing_game 
	main.cpp
	game.cpp
	gui.cpp
	paragraph.cpp	
)

target_link_libraries(typing_game vulkan)
target_link_libraries(typing_game SDL2)
