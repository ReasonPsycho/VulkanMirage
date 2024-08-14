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
    std::optional<uint32_t> presentFamily;

    bool isComplete() {
        return graphicsFamily.has_value() && presentFamily.has_value();
    }
};

struct SwapChainSupportDetails {
    VkSurfaceCapabilitiesKHR capabilities;
    std::vector<VkSurfaceFormatKHR> formats;
    std::vector<VkPresentModeKHR> presentModes;
};

class VulkanMiragePathtracer {
public:
    void run();

private:
    void initWindow();

    void initVulkan();

    void createInstance();

    void setupDebugMessenger();

    std::vector<const char *> getRequiredExtensions();

    void mainLoop();

    void cleanup();
    void createRenderPass();
    bool checkValidationLayerSupport();

    void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT &createInfo);

    void pickPhysicalDevice();

    void createLogicalDevice();
    void createGraphicsPipeline();
    VkShaderModule createShaderModule(const std::vector<char>& code);

    void createSurface();
    void     createImageViews();

    bool isDeviceSuitable(VkPhysicalDevice device);

    QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);

    bool checkDeviceExtensionSupport(VkPhysicalDevice device, const std::vector<const char *> &requiredExtensions);

    static std::vector<char> readFile(const std::string& filename);

    static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
        VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
        VkDebugUtilsMessageTypeFlagsEXT messageType,
        const VkDebugUtilsMessengerCallbackDataEXT *pCallbackData,
        void *pUserData);

    VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT *pCreateInfo,
                                          const VkAllocationCallbacks *pAllocator,
                                          VkDebugUtilsMessengerEXT *pDebugMessenger);

    void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger,
                                       const VkAllocationCallbacks *pAllocator);

    SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);
    VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
    VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
    VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);
    void createSwapChain();
    
    const uint32_t WIDTH = 800;
    const uint32_t HEIGHT = 600;

    const std::vector<const char *> validationLayers = {
        "VK_LAYER_KHRONOS_validation"
    };

    VkPipeline graphicsPipeline;
    VkRenderPass renderPass;
    VkPipelineLayout pipelineLayout;
    std::vector<VkImageView> swapChainImageViews;
    VkFormat swapChainImageFormat;
    VkExtent2D swapChainExtent;
    std::vector<VkImage> swapChainImages;
    VkSwapchainKHR swapChain;
    VkQueue presentQueue;
    VkQueue graphicsQueue;
    VkDevice device;
    VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
    SDL_Window *window;
    VkInstance instance;
    VkDebugUtilsMessengerEXT debugMessenger;
    VkSurfaceKHR surface;

#ifdef DEBUG_BUILD
    const bool enableValidationLayers = true;
#else
    const bool enableValidationLayers = false;
#endif
};


#endif //VULKANMIRAGEPATHTRACER_H
