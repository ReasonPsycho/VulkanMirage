//
// Created by redkc on 14/08/2024.
//

#ifndef VULKANMIRAGEPATHTRACER_H
#define VULKANMIRAGEPATHTRACER_H

#include <array>
#include <glm/glm.hpp>
#include <vulkan/vulkan.h>

#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_vulkan.h"

#include <SDL2/SDL.h>
#include <SDL_vulkan.h>
#include <glm/gtx/transform.hpp>
#include <algorithm>
#include <chrono>
#include <fstream>
#include <set>
#include "model/Model.h"
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



struct UniformBufferObject {
    alignas(16) glm::mat4 model;
    alignas(16) glm::mat4 view;
    alignas(16) glm::mat4 proj;
};

class VulkanMiragePathtracer {
public:
    void run();

private:
    void initWindow();

    void createDescriptorSets();

    void createTextureImageView();

    void createTextureSampler();

    void createDepthResources();

    void loadModel();

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
    void initImgui();
    QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);

    bool checkDeviceExtensionSupport(VkPhysicalDevice device, const std::vector<const char *> &requiredExtensions);
    VkFormat findSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features);
    VkFormat findDepthFormat();
    bool hasStencilComponent(VkFormat format);

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
    void createFramebuffers();
    void createCommandPool();
    void createTextureImage();
    static void check_vk_result(VkResult err);

    void createCommandBuffers();
    void recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);
   void drawFrame();
    void createSyncObjects();
    void recreateSwapChain();
    void cleanupSwapChain();
    void createVertexBuffer();
    uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
    void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
    void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);
    void createDescriptorSetLayout();
    void updateUniformBuffer(uint32_t currentImage);
    void createDescriptorPool();
    void createImage(uint32_t width, uint32_t height, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage& image, VkDeviceMemory& imageMemory);
    void transitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout);
    void copyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height);

 void FrameRender(ImGui_ImplVulkanH_Window* wd, ImDrawData* draw_data);

    void FramePresent(ImGui_ImplVulkanH_Window* wd);

    void createIndexBuffer();
void     createUniformBuffers();


    VkCommandBuffer beginSingleTimeCommands();

    void endSingleTimeCommands(VkCommandBuffer commandBuffer);

    const int MAX_FRAMES_IN_FLIGHT = 2;
    const int minImages = 2;

    bool framebufferResized = false;
    bool isMinimized = false;

    const uint32_t WIDTH = 800;
    const uint32_t HEIGHT = 600;
    Model *model;
    VkBuffer vertexBuffer;
    VkDeviceMemory vertexBufferMemory;
    ImGuiIO io;
    const std::vector<const char *> validationLayers = {
        "VK_LAYER_KHRONOS_validation"
    };
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    ImGui_ImplVulkanH_Window imguiWindow ;
    VkImage depthImage;
    VkDeviceMemory depthImageMemory;
    VkImageView depthImageView;
    VkImageView createImageView(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags);
    VkImageView textureImageView;
    VkSampler textureSampler;
    VkPipelineStageFlags sourceStage;
    VkPipelineStageFlags destinationStage;
    VkBuffer indexBuffer;
    VkDeviceMemory indexBufferMemory;
    VkImage textureImage;
    VkDeviceMemory textureImageMemory;
    VkBuffer stagingBuffer;
    VkDeviceMemory stagingBufferMemory;
    VkDescriptorPool descriptorPool;
    std::vector<VkDescriptorSet> descriptorSets;
    std::vector<VkBuffer> uniformBuffers;
    std::vector<VkDeviceMemory> uniformBuffersMemory;
    std::vector<void*> uniformBuffersMapped;
    VkDescriptorSetLayout descriptorSetLayout;
    VkPipelineLayout pipelineLayout;
    uint32_t currentFrame = 0;
    std::vector<VkSemaphore> imageAvailableSemaphores;
    std::vector<VkSemaphore> renderFinishedSemaphores;
    std::vector<VkFence> inFlightFences;
    std::vector<VkCommandBuffer> commandBuffers;    
    VkCommandPool commandPool;
    VkPipeline graphicsPipeline;
    VkRenderPass renderPass;
    std::vector<VkFramebuffer> swapChainFramebuffers;
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

inline void VulkanMiragePathtracer::createDescriptorPool() {
    std::array<VkDescriptorPoolSize, 2> poolSizes{};
    poolSizes[0].type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    poolSizes[0].descriptorCount = static_cast<uint32_t>(MAX_FRAMES_IN_FLIGHT);
    poolSizes[1].type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
    poolSizes[1].descriptorCount = static_cast<uint32_t>(MAX_FRAMES_IN_FLIGHT * 2); //TODO ensure i don't wase space couse imgui XD

    VkDescriptorPoolCreateInfo poolInfo{};
    poolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
    poolInfo.flags = VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT; // needed by imgui
    poolInfo.poolSizeCount = static_cast<uint32_t>(poolSizes.size());
    poolInfo.pPoolSizes = poolSizes.data();
    poolInfo.maxSets = static_cast<uint32_t>(MAX_FRAMES_IN_FLIGHT * 2);

    if (vkCreateDescriptorPool(device, &poolInfo, nullptr, &descriptorPool) != VK_SUCCESS) {
        throw std::runtime_error("failed to create descriptor pool!");
    }
}

inline void VulkanMiragePathtracer::createBuffer(VkDeviceSize size, VkBufferUsageFlags usage,
                                                 VkMemoryPropertyFlags properties, VkBuffer&buffer, VkDeviceMemory&bufferMemory) {
    VkBufferCreateInfo bufferInfo{};
    bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    bufferInfo.size = size;
    bufferInfo.usage = usage;
    bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

    if (vkCreateBuffer(device, &bufferInfo, nullptr, &buffer) != VK_SUCCESS) {
        throw std::runtime_error("failed to create buffer!");
    }

    VkMemoryRequirements memRequirements;
    vkGetBufferMemoryRequirements(device, buffer, &memRequirements);

    VkMemoryAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    allocInfo.allocationSize = memRequirements.size;
    allocInfo.memoryTypeIndex = findMemoryType(memRequirements.memoryTypeBits, properties);

    if (vkAllocateMemory(device, &allocInfo, nullptr, &bufferMemory) != VK_SUCCESS) {
        throw std::runtime_error("failed to allocate buffer memory!");
    }

    vkBindBufferMemory(device, buffer, bufferMemory, 0);
}


#endif //VULKANMIRAGEPATHTRACER_H
