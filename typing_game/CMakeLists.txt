cmake_minimum_required(VERSION 3.10)

add_executable(
	TypingGame

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


find_package(Vulkan REQUIRED)
find_package(SDL2 REQUIRED)

include_directories(${VULKAN_INCLUDE_DIR})
include_directories(${SDL2_INCLIDE_DIRS})

target_link_libraries(TypingGame ${VULKAN_LIB_LIST})
target_link_libraries(TypingGame ${SDL2_LIBRARIES})
target_link_libraries(TypingGame lib_imgui)

target_include_directories(TypingGame PUBLIC lib_imgui)