#include <string>
#include <stdexcept>
#include <iostream>
#include <vector>

#include <SDL2/SDL.h>
#include <SDL2/SDL_vulkan.h>
#include <vector>
#include <vulkan/vulkan.h>
#include <vulkan/vulkan_core.h>

#include "gui.hpp"

GUI::GUI() {
	try {
		initialise();
	}

	catch (std::runtime_error& e) {
		std::cerr << e.what() << std::endl;
		exit(1);
	}
}

GUI::~GUI() {
	VkResult result = vkDeviceWaitIdle(VulkanInfo.device);
    errorCheck(result);

    cleanUpVulkanWindow();
    cleanUpVulkan();
}

const bool GUI::running() {
	return true;
}

void GUI::initialise() {

	initialiseSDL();
	//initialiseVulkan();
	// selectGPU();
}

void GUI::initialiseVulkan() {
	VkInstanceCreateInfo info {};
	info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	info.pApplicationInfo = &VulkanInfo.app_info;
	info.enabledLayerCount = layer_names.size();
	info.ppEnabledLayerNames = layer_names.data();
	info.enabledExtensionCount = extension_names.size();
	info.ppEnabledExtensionNames = extension_names.data();

	VkResult error_code;
	error_code = vkCreateInstance(&info, nullptr, &VulkanInfo.instance);
	errorCheck(error_code);
}

void GUI::initialiseSDL() {
	int renderer_flags = SDL_RENDERER_ACCELERATED;
	int window_flags = (SDL_WindowFlags)(SDL_WINDOW_VULKAN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) != 0) {
		throw std::runtime_error("Couldn't initialise SDL");
	}

	SDLInfo.window = SDL_CreateWindow("TESTT", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SDLInfo.width, SDLInfo.height, window_flags);

	if (!SDLInfo.window) {
		throw std::runtime_error("Couldn't initialise SDL");
	}

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

	SDLInfo.renderer = SDL_CreateRenderer(SDLInfo.window, -1, renderer_flags);

	SDL_Vulkan_GetInstanceExtensions(SDLInfo.window, &extensions_count, nullptr);
	extension_names.resize(extensions_count);
	SDL_Vulkan_GetInstanceExtensions(SDLInfo.window, &extensions_count, extension_names.data());

	if (!SDLInfo.renderer) {
		throw std::runtime_error("Couldn't initialise SDL");
	}
}

void GUI::earlyUpdate() {
	
}

void GUI::update() {

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

void GUI::errorCheck(VkResult result) {
	if (result == 0) {
		return;
	}
	std::cerr << "[vulkan] Error code: " << result << std::endl;
	if (result < 0) {
		std::abort();
	}
}

VkPhysicalDevice GUI::selectGPU() {
	uint32_t gpu_count;
	VkResult error_code = vkEnumeratePhysicalDevices(VulkanInfo.instance, &gpu_count, nullptr);
	errorCheck(error_code);

	std::vector<VkPhysicalDevice> gpus;
	gpus.resize(gpu_count);
	error_code = vkEnumeratePhysicalDevices(VulkanInfo.instance, &gpu_count, gpus.data());
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

void GUI::cleanUpVulkanWindow() {

}

void GUI::cleanUpVulkan() {
	vkDestroyDescriptorPool(VulkanInfo.device, VulkanInfo.descriptor_pool, VulkanInfo.allocator);

    vkDestroyDevice(VulkanInfo.device, VulkanInfo.allocator);
    vkDestroyInstance(VulkanInfo.instance, VulkanInfo.allocator);
}
