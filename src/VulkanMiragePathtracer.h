//
// Created by redkc on 14/08/2024.
//

#ifndef VULKANMIRAGEPATHTRACER_H
#define VULKANMIRAGEPATHTRACER_H

#include <vulkan/vulkan.h>
#include <SDL2/SDL.h>
#include <SDL_vulkan.h>

#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <optional>
#include <vector>

struct QueueFamilyIndices {
    std::optional<uint32_t> graphicsFamily;

    bool isComplete() {
        return graphicsFamily.has_value();
    }
};


class VulkanMiragePathtracer {
public:
    void run();
private:
    void initWindow();
    void initVulkan();
    void createInstance();
   void setupDebugMessenger();
    std::vector<const char*> getRequiredExtensions();
    void mainLoop();
    void cleanup();
    bool checkValidationLayerSupport();
    void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
    void pickPhysicalDevice();
    void createLogicalDevice();

    bool isDeviceSuitable(VkPhysicalDevice device);
    QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);

    bool checkDeviceExtensionSupport(VkPhysicalDevice device, const std::vector<const char *> &requiredExtensions);

    static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
        VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
        VkDebugUtilsMessageTypeFlagsEXT messageType,
        const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
        void* pUserData);
    VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger);
    void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator);

    const uint32_t WIDTH = 800;
    const uint32_t HEIGHT = 600;

    const std::vector<const char*> validationLayers = {
        "VK_LAYER_KHRONOS_validation"
    };

    VkQueue graphicsQueue;
    VkDevice device;
    VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
    SDL_Window *window;
    VkInstance instance;
    VkDebugUtilsMessengerEXT debugMessenger;

#ifdef DEBUG_BUILD
    const bool enableValidationLayers = true;
#else
    const bool enableValidationLayers = false;
#endif
};



#endif //VULKANMIRAGEPATHTRACER_H
