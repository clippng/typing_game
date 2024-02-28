cmake_minimum_required(VERSION 3.10)

add_executable(
	typing_game

	main.cpp
	game.cpp
	gui.cpp
	paragraph.cpp
	smart_pointer_wrapper.cpp

	main.hpp
	game.hpp
	gui.hpp
	paragraph.hpp
	smart_pointer_wrapper.hpp
)

add_subdirectory(lib_imgui)

target_link_libraries(typing_game ${VULKAN_LIB_LIST})
target_link_libraries(typing_game ${SDL2_LIBRARIES})
target_link_libraries(typing_game lib_imgui)

target_include_directories(typing_game PUBLIC lib_imgui)