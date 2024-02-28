cmake_minimum_required(VERSION 3.10)

add_library(
	lib_imgui

	imconfig.h
	imgui_demo.cpp
	imgui_draw.cpp
	imgui_impl_sdl2.cpp
	imgui_impl_sdl2.h
	imgui_impl_vulkan.cpp
	imgui_impl_vulkan.h
	imgui_internal.h
	imgui_stdlib.cpp
	imgui_tables.cpp
	imgui_widgets.cpp
	imgui.cpp
	imgui.h
	imstb_rectpack.h
	imstb_textedit.h
	imstb_truetype.h
)

target_link_libraries(lib_imgui ${VULKAN_LIB_LIST})
target_link_libraries(lib_imgui ${SDL2_LIBRARIES})