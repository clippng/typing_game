#pragma once 

#include <SDL2/SDL_events.h>
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
#include <vulkan/vulkan_beta.h>

#include "../lib_imgui/imgui.h"
#include "../lib_imgui/imgui_impl_sdl2.h"
#include "../lib_imgui/imgui_impl_vulkan.h"
#include "smart_pointer_wrapper.hpp"
#include "smart_pointer_wrapper.cpp"

#define _DEBUG // this isnt right
//#define VK_KHR_PORTABILITY_SUBSET_EXTENSION_NAME

#ifdef _DEBUG
#define APP_USE_VULKAN_DEBUG_REPORT
#endif

class GUI {
public:
	GUI();
	~GUI();

	void initialise();
	void initialiseVulkan(ImVector<const char*> instance_extensions);
	void initialiseImGui();
	void initialiseSDL();

	void earlyUpdate();
	void update();
	void render(); // late update
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
	
	VkAllocationCallbacks* allocator = nullptr;
	VkInstance instance = VK_NULL_HANDLE;
	VkDebugReportCallbackEXT debug_report = VK_NULL_HANDLE;
	VkPhysicalDevice physical_device = VK_NULL_HANDLE;
	VkDevice device = VK_NULL_HANDLE;
	VkQueue queue = VK_NULL_HANDLE;
	VkDescriptorPool descriptor_pool = VK_NULL_HANDLE;
	VkPipelineCache pipeline_cache = VK_NULL_HANDLE;
	uint32_t queue_family = (uint32_t) - 1;

	SDL_Event event;

	ImGuiIO io;

	VkCommandBuffer command_buffer = VK_NULL_HANDLE;

	ImGui_ImplVulkanH_Window main_window_data;
	uint32_t min_image_count = 2;
	bool swap_chain_rebuild = false;
	
	bool extensionCheckAvailable(const ImVector<VkExtensionProperties>& properties, const char* extension);
	VkPhysicalDevice selectGPU(); 

	void cleanUpVulkanWindow();
	void cleanUpVulkan();

	static void errorCheck(VkResult result);

	#ifdef APP_USE_VULKAN_DEBUG_REPORT
	static VKAPI_ATTR VkBool32 VKAPI_CALL debugReport(VkDebugReportFlagsEXT flags, VkDebugReportObjectTypeEXT objectType, uint64_t object, size_t location, int32_t messageCode, const char* pLayerPrefix, const char* pMessage, void* pUserData);
	#endif 
};