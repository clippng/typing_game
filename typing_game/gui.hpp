#pragma once 

#include <SDL2/SDL_events.h>
#include <string>

#include <SDL2/SDL.h>
#include <vector>
#include <vulkan/vulkan.h>
#include <vulkan/vulkan_core.h>

class GUI {
public:
	GUI();
	~GUI();

	void initialise();
	void initialiseVulkan();
	void initialiseSDL();

	void earlyUpdate();
	void update();
	void render(); // late update
	void handleInput();

private:
	struct {
		SDL_Renderer *renderer;
		SDL_Window *window;

		int width = 1280;
		int height = 720;

		SDL_Event event;
	} SDLInfo;

	uint32_t extensions_count = 0;
	std::vector<const char *> extension_names;
	std::vector<const char *> layer_names;
	
	const std::string title = "Typing Game";
	const std::string header = "test";
	const std::string paragraph = "This is a test paragraph idk how long it has to be to go over lines but hopefully this is enough";
	
	struct {
		VkAllocationCallbacks* allocator = nullptr;
		VkInstance instance = VK_NULL_HANDLE;
		VkDebugReportCallbackEXT debug_report = VK_NULL_HANDLE;
		VkPhysicalDevice physical_device = VK_NULL_HANDLE;
		VkDevice device = VK_NULL_HANDLE;
		VkQueue queue = VK_NULL_HANDLE;
		VkDescriptorPool descriptor_pool = VK_NULL_HANDLE;
		VkPipelineCache pipeline_cache = VK_NULL_HANDLE;
		uint32_t queue_family = (uint32_t) - 1;

		VkCommandBuffer command_buffer = VK_NULL_HANDLE;

		VkApplicationInfo app_info;
	} VulkanInfo;


	VkCommandBuffer command_buffer = VK_NULL_HANDLE;

	uint32_t min_image_count = 2;
	bool swap_chain_rebuild = false;
	
	VkPhysicalDevice selectGPU(); 

	void cleanUpVulkanWindow();
	void cleanUpVulkan();

	static void errorCheck(VkResult result);

};