#include "gui.hpp"

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

GUI::~GUI() {
	VkResult result = vkDeviceWaitIdle(device);
    errorCheck(result);
    ImGui_ImplVulkan_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    cleanUpVulkanWindow();
    cleanUpVulkan();
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
	VkResult error_code;
	
	{
		VkInstanceCreateInfo create_info = {};
		create_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;

		uint32_t properties_count;
		ImVector<VkExtensionProperties> properties;
		vkEnumerateInstanceExtensionProperties(nullptr, &properties_count, nullptr);
		properties.resize(properties_count);
		error_code = vkEnumerateInstanceExtensionProperties(nullptr, &properties_count, properties.Data);
		errorCheck(error_code);

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
		error_code = vkCreateInstance(&create_info, allocator, &instance);
		errorCheck(error_code);

		#ifdef APP_USE_VULKAN_DEBUG_REPORT

		auto vkCreateDebugReportCallbakcEXT = (PFN_vkCreateDebugReportCallbackEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugReportCallbackEXT");
		IM_ASSERT(vkCreateDebugReportCallbakcEXT != nullptr);
		VkDebugReportCallbackCreateInfoEXT debug_report_create_info = {};
		debug_report_create_info.sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CALLBACK_CREATE_INFO_EXT;
		debug_report_create_info.flags = VK_DEBUG_REPORT_ERROR_BIT_EXT | VK_DEBUG_REPORT_WARNING_BIT_EXT | VK_DEBUG_REPORT_PERFORMANCE_WARNING_BIT_EXT;
		debug_report_create_info.pfnCallback = debugReport;
		error_code = vkCreateDebugReportCallbakcEXT(instance, &debug_report_create_info, allocator, &debug_report);
		errorCheck(error_code);
		#endif
	}

	physical_device = selectGPU();

	{
		uint32_t count;
		vkGetPhysicalDeviceQueueFamilyProperties(physical_device, &count, nullptr);
		std::unique_ptr<VkQueueFamilyProperties> queues;
		vkGetPhysicalDeviceQueueFamilyProperties(physical_device, &count, queues.get());	

		for (uint32_t i = 0; i < count; ++i) {
			if (queues.get()[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) {
				queue_family = i;
				break;
			}
		}

		IM_ASSERT(queue_family != (uint32_t) - 1);
		
	}

	{
		ImVector<const char*> device_extensions;
		device_extensions.push_back("VK_KHR_swapchain");

		uint32_t properties_count;
		ImVector<VkExtensionProperties> properties;
		vkEnumerateDeviceExtensionProperties(physical_device, nullptr, &properties_count,  nullptr);
		properties.resize(properties_count);
		vkEnumerateDeviceExtensionProperties(physical_device, nullptr, &properties_count, properties.Data);
	
		#ifdef VK_KHR_PORTABILITY_SUBSET_EXTENSION_NAME
		if (extensionCheckAvailable(properties, VK_KHR_PORTABILITY_SUBSET_EXTENSION_NAME)) {
			device_extensions.push_back(VK_KHR_PORTABILITY_SUBSET_EXTENSION_NAME);
		}
		#endif

		const float queue_priority[] = {1.0f};

		VkDeviceQueueCreateInfo queue_info[1] = {};
		queue_info[0].sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
		queue_info[0].queueFamilyIndex = queue_family;
		queue_info[0].queueCount = 1;
		queue_info[0].pQueuePriorities = queue_priority;

		VkDeviceCreateInfo create_info = {};
		create_info.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
		create_info.queueCreateInfoCount = sizeof(queue_info) / sizeof(queue_info[0]);
		create_info.pQueueCreateInfos = queue_info;
		create_info.enabledExtensionCount = (uint32_t)device_extensions.Size;
		create_info.ppEnabledExtensionNames = device_extensions.Data;
		error_code = vkCreateDevice(physical_device, &create_info, allocator, &device);
		errorCheck(error_code);

		vkGetDeviceQueue(device, queue_family, 0, &queue);
	}

	{
		VkDescriptorPoolSize pool_sizes[] = {
			{VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, 1},
		};
		VkDescriptorPoolCreateInfo pool_info = {};
		pool_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
		pool_info.flags = VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT;
		pool_info.maxSets = 1;
		pool_info.poolSizeCount = (uint32_t)IM_ARRAYSIZE(pool_sizes);
		pool_info.pPoolSizes = pool_sizes;
		error_code = vkCreateDescriptorPool(device, &pool_info, allocator, &descriptor_pool);
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

void GUI::errorCheck(VkResult result) {
	if (result == 0) {
		return;
	}
	std::cerr << "[vulkan] Error code: " << result << std::endl;
	if (result < 0) {
		std::abort();
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
	VkResult result = vkEnumeratePhysicalDevices(instance, &gpu_count, nullptr);
	//check for errors
	IM_ASSERT(gpu_count < 0);

	ImVector<VkPhysicalDevice> gpus;
	gpus.resize(gpu_count);
	result = vkEnumeratePhysicalDevices(instance, &gpu_count, gpus.Data);
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
	ImGui_ImplVulkanH_DestroyWindow(instance, device, &main_window_data, allocator);
}

void GUI::cleanUpVulkan() {
	vkDestroyDescriptorPool(device, descriptor_pool, allocator);

	#ifdef APP_USE_VULKAN_DEBUG_REPORT
    auto vkDestroyDebugReportCallbackEXT = (PFN_vkDestroyDebugReportCallbackEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugReportCallbackEXT");
    vkDestroyDebugReportCallbackEXT(instance, debug_report, allocator);
	#endif 

    vkDestroyDevice(device, allocator);
    vkDestroyInstance(instance, allocator);
}

VKAPI_ATTR VkBool32 VKAPI_CALL GUI::debugReport(VkDebugReportFlagsEXT flags, VkDebugReportObjectTypeEXT objectType, uint64_t object, size_t location, int32_t messageCode, const char* pLayerPrefix, const char* pMessage, void* pUserData) {
    (void)flags; (void)object; (void)location; (void)messageCode; (void)pUserData; (void)pLayerPrefix; // Unused arguments
    fprintf(stderr, "[vulkan] Debug report from ObjectType: %i\nMessage: %s\n\n", objectType, pMessage);
    return VK_FALSE;
}
