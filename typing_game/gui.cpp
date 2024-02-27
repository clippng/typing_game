#include "gui.hpp"
#include "lib_imgui/imgui.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_hints.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_vulkan.h>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <stdexcept>
#include <vulkan/vulkan_core.h>


GUI::GUI() {
	ImGui::CreateContext(); 

	try {
		initialise();
	}

	catch (std::runtime_error& e) {
		std::cerr << e.what() << std::endl;
		exit(1);
	}

}

void GUI::initialise() {
	int renderer_flags = SDL_RENDERER_ACCELERATED;
	int window_flags = (SDL_WindowFlags)(SDL_WINDOW_VULKAN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) != 0) {
		throw std::runtime_error("Couldn't initialise SDL");
	}

	SDLWindow.window = SDL_CreateWindow("TESTT", SDL_WINDOWPOS_CENTERED, 
		SDL_WINDOWPOS_CENTERED, 1280, 720, window_flags);

	if (!SDLWindow.window) {
		throw std::runtime_error("Couldn't initialise SDL");
	}

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

	SDLWindow.renderer = SDL_CreateRenderer(SDLWindow.window, -1, renderer_flags);
	extensions.resize(extensions_count);
	SDL_Vulkan_GetInstanceExtensions(SDLWindow.window, &extensions_count, extensions.Data);
	
	try {
		setupVulkan(extensions);
	}

	catch (std::runtime_error& e) {
		std::cerr << e.what() << std::endl;
	}

	if (!SDLWindow.renderer) {
		throw std::runtime_error("Couldn't initialise SDL");
	}

	SDL_Vulkan_GetInstanceExtensions(SDLWindow.window, &extensions_count, nullptr);
}

void GUI::setupVulkan(ImVector<const char*> instance_extensions) {
	VkResult result;

	g_allocator = nullptr;
	g_instance = VK_NULL_HANDLE;
	g_debug_report = VK_NULL_HANDLE;
	g_queue = VK_NULL_HANDLE;
	g_queue_family = (uint32_t) - 1;
	
	{
		VkInstanceCreateInfo create_info = {};
		create_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;

		uint32_t properties_count;
		ImVector<VkExtensionProperties> properties;
		vkEnumerateInstanceExtensionProperties(nullptr, &properties_count, nullptr);
		properties.resize(properties_count);
		result = vkEnumerateInstanceExtensionProperties(nullptr, &properties_count, properties.Data);
		
		if (result < 0) {
			throw std::runtime_error("Couldn't initialsie Vulkan");
		}

		if (extensionCheckAvailable(properties, VK_KHR_GET_PHYSICAL_DEVICE_PROPERTIES_2_EXTENSION_NAME)) {
			instance_extensions.push_back(VK_KHR_GET_PHYSICAL_DEVICE_PROPERTIES_2_EXTENSION_NAME);
		}

		#ifdef VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME

		if (extensionCheckAvailable(properties, VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME)) {
			instance_extensions.push_back(VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME);
			create_info.flags |= VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR;
		}
		#endif

		#ifdef APP_USE_VULKAN_DEBUG_REPORT

		const char* layers[] = {"VK_LAYER_KHRONOS_validation"};
		create_info.enabledLayerCount = 1;
		create_info.ppEnabledLayerNames = layers;
		instance_extensions.push_back("VK_EXT_debug_report");
		#endif

		create_info.enabledExtensionCount = (uint32_t)instance_extensions.Size;
		create_info.ppEnabledExtensionNames = instance_extensions.Data;
		result = vkCreateInstance(&create_info, g_allocator, &g_instance);

		if (result < 0) {
			throw std::runtime_error("Couldn't initialsie Vulkan");
		}

		#ifdef APP_USE_VULKAN_DEBUG_REPORT

		auto vkCreateDebugReportCallbakcEXT = (PFN_vkCreateDebugReportCallbackEXT)vkGetInstanceProcAddr(g_instance, "vkCreateDebugReportCallbackEXT");
		IM_ASSERT(vkCreateDebugReportCallbakcEXT != nullptr);
		VkDebugReportCallbackCreateInfoEXT debug_report_create_info = {};
		debug_report_create_info.sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CALLBACK_CREATE_INFO_EXT;
		debug_report_create_info.flags = VK_DEBUG_REPORT_ERROR_BIT_EXT | VK_DEBUG_REPORT_WARNING_BIT_EXT | VK_DEBUG_REPORT_PERFORMANCE_WARNING_BIT_EXT;
		debug_report_create_info.pfnCallback = debug_report;
		result = vkCreateDebugReportCallbakcEXT(g_instance, &debug_report_create_info, g_allocator, &g_debug_report);

		if (result < 0) {
			throw std::runtime_error("Couldn't initialise Vulkan");
		}
		#endif
	}

	g_physical_device = selectGPU();

	{
		uint32_t count;
		vkGetPhysicalDeviceQueueFamilyProperties(g_physical_device, &count, nullptr);
		std::unique_ptr<VkQueueFamilyProperties> queues;
		vkGetPhysicalDeviceQueueFamilyProperties(g_physical_device, &count, queues.get());	

		for (uint32_t i = 0; i < count; ++i) {
			if (queues.get()[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) {
				g_queue_family = i;
				break;
			}
		}
		
	}
}

void GUI::update() {
	ImGui::NewFrame();
	ImGui::Render();
}

void GUI::render() {

}

void GUI::handleInput() {
	SDL_Event event;

	while (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_QUIT:
				exit(0);
				break;
			default:
				break;
		}
	}
}

bool GUI::extensionCheckAvailable(const ImVector<VkExtensionProperties>& properties, const char* extension) {
	for (const VkExtensionProperties& p : properties) {
		if (strcmp(p.extensionName, extension) == 0) {
			return true;
		} 
	}
	return false;
}

VkPhysicalDevice GUI::selectGPU() {
	uint32_t gpu_count;
	VkResult result = vkEnumeratePhysicalDevices(g_instance, &gpu_count, nullptr);
	//check for errors
	IM_ASSERT(gpu_count < 0);

	ImVector<VkPhysicalDevice> gpus;
	gpus.resize(gpu_count);
	result = vkEnumeratePhysicalDevices(g_instance, &gpu_count, gpus.Data);
	//check for errors

	for (VkPhysicalDevice& device : gpus) {
		VkPhysicalDeviceProperties properties;
		vkGetPhysicalDeviceProperties(device, &properties);
		if (properties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU) {
			return device;
		}
	}

	if (gpu_count > 0) {
		return gpus[0];
	}
	return VK_NULL_HANDLE;
}

VKAPI_ATTR VkBool32 VKAPI_CALL GUI::debug_report(VkDebugReportFlagsEXT flags, VkDebugReportObjectTypeEXT objectType, uint64_t object, size_t location, int32_t messageCode, const char* pLayerPrefix, const char* pMessage, void* pUserData) {
    (void)flags; (void)object; (void)location; (void)messageCode; (void)pUserData; (void)pLayerPrefix; // Unused arguments
    fprintf(stderr, "[vulkan] Debug report from ObjectType: %i\nMessage: %s\n\n", objectType, pMessage);
    return VK_FALSE;
}
