#pragma once 

#include <SDL2/SDL_render.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_video.h>
#include <cstdint>
#include <memory>
#include <string>
#include <stdexcept>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_vulkan.h>
#include <vulkan/vulkan.h>
#include <vulkan/vulkan_core.h>

#include "lib_imgui/imgui.h"
#include "lib_imgui/imgui_impl_sdl2.h"
#include "lib_imgui/imgui_impl_vulkan.h"
#include "smart_pointer_wrapper.hpp"
#include "smart_pointer_wrapper.cpp"

#define _DEBUG // this isnt right
#ifdef _DEBUG
#define APP_USE_VULKAN_DEBUG_REPORT
#endif

class GUI {
public:
	GUI();

	void initialise();
	void setupVulkan(ImVector<const char*> instance_extensions);

	void update();
	void render();
	void handleInput();

private:
	struct {
		SDL_Renderer *renderer;
		SDL_Window *window;
	} SDLWindow;

	ImVector<const char*> extensions;
	uint32_t extensions_count = 0;
	
	const std::string title = "Typing Game";
	const std::string header = "test";
	const std::string paragraph = "This is a test paragraph idk how long it has to be to go over lines but hopefully this is enough";
	
	static VkAllocationCallbacks* g_allocator;
	static VkInstance g_instance;
	static VkDebugReportCallbackEXT g_debug_report;
	static VkPhysicalDevice g_physical_device;
	static VkQueue g_queue;
	static uint32_t g_queue_family;
	
	static bool extensionCheckAvailable(const ImVector<VkExtensionProperties>& properties, const char* extension);
	static VkPhysicalDevice selectGPU(); 

	#ifdef APP_USE_VULKAN_DEBUG_REPORT
	static VKAPI_ATTR VkBool32 VKAPI_CALL debug_report(VkDebugReportFlagsEXT flags, VkDebugReportObjectTypeEXT objectType, uint64_t object, size_t location, int32_t messageCode, const char* pLayerPrefix, const char* pMessage, void* pUserData);
	#endif 
};