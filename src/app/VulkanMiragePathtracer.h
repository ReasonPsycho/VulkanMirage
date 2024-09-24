//
// Created by redkc on 14/08/2024.
//

#ifndef VULKANMIRAGEPATHTRACER_H
#define VULKANMIRAGEPATHTRACER_H
#define VK_CHECK_RESULT(f)                                                                                       \
{                                                                                                                 \
VkResult res = (f);                                                                                           \
if (res != VK_SUCCESS)                                                                                        \
{                                                                                                             \
std::cout << "Fatal : VkResult is \"" << res << "\" in " << __FILE__ << " at line " << __LINE__ << "\n";  \
assert(res == VK_SUCCESS);                                                                                \
}                                                                                                             \
}
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

#include "VulkanBuffer.h"

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

// Holds data for a ray tracing scratch buffer that is used as a temporary storage
struct RayTracingScratchBuffer {
    uint64_t deviceAddress = 0;
    VkBuffer handle = VK_NULL_HANDLE;
    VkDeviceMemory memory = VK_NULL_HANDLE;
};

// Ray tracing acceleration structure
struct AccelerationStructure {
    VkAccelerationStructureKHR handle;
    uint64_t deviceAddress = 0;
    VkDeviceMemory memory;
    VkBuffer buffer;
};

class VulkanMiragePathtracer {
public:
    void run();

    PFN_vkGetBufferDeviceAddressKHR vkGetBufferDeviceAddressKHR;
    PFN_vkCreateAccelerationStructureKHR vkCreateAccelerationStructureKHR;
    PFN_vkDestroyAccelerationStructureKHR vkDestroyAccelerationStructureKHR;
    PFN_vkGetAccelerationStructureBuildSizesKHR vkGetAccelerationStructureBuildSizesKHR;
    PFN_vkGetAccelerationStructureDeviceAddressKHR vkGetAccelerationStructureDeviceAddressKHR;
    PFN_vkCmdBuildAccelerationStructuresKHR vkCmdBuildAccelerationStructuresKHR;
    PFN_vkBuildAccelerationStructuresKHR vkBuildAccelerationStructuresKHR;
    PFN_vkCmdTraceRaysKHR vkCmdTraceRaysKHR;
    PFN_vkGetRayTracingShaderGroupHandlesKHR vkGetRayTracingShaderGroupHandlesKHR;
    PFN_vkCreateRayTracingPipelinesKHR vkCreateRayTracingPipelinesKHR;

    VkPhysicalDeviceRayTracingPipelinePropertiesKHR rayTracingPipelineProperties{};
    VkPhysicalDeviceAccelerationStructureFeaturesKHR accelerationStructureFeatures{};

    struct StorageImage {
        VkDeviceMemory memory;
        VkImage image;
        VkImageView view;
        VkFormat format;
    } storageImage;

private:
    void initWindow();

    void initWindow2();

    void createDescriptorSets();

    void createTextureImageView();

    void createTextureSampler();

    void createDepthResources();

    void loadModel();

    void createAccelerationStructure();

    void createAccelarationStructure();

    void prepareRaytracing();

    void buildCommandBuffers();

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

    VkShaderModule createShaderModule(const std::vector<char> &code);

    void createSurface();

    void createSurface2();

    void createImageViews();

    bool isDeviceSuitable(VkPhysicalDevice device);

    void initImgui();

    QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);

    bool checkDeviceExtensionSupport(VkPhysicalDevice device, const std::vector<const char *> &requiredExtensions);

    VkFormat findSupportedFormat(const std::vector<VkFormat> &candidates, VkImageTiling tiling,
                                 VkFormatFeatureFlags features);

    VkFormat findDepthFormat();

    bool hasStencilComponent(VkFormat format);

    static std::vector<char> readFile(const std::string &filename);

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

    VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR> &availableFormats);

    VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR> &availablePresentModes);

    VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR &capabilities, SDL_Window *window);

    void createSwapChain();

    void createSwapChain2();

    void createFramebuffers();

    void createCommandPool();

    void createCommandPool2();

    void createTextureImage();

    static void check_vk_result(VkResult err);

    void createCommandBuffers();

    void recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);

    void recordCommandBuffer2(VkCommandBuffer commandBuffer, uint32_t imageIndex);

    void drawFrame();

    void drawFrame2();

    void createSyncObjects();

    void createSyncObjects2();

    void recreateSwapChain();

    void cleanupSwapChain();

    void createVertexBuffer();

    uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);

    void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer &buffer,
                      VkDeviceMemory &bufferMemory);

    void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);

    void createDescriptorSetLayout();

    void updateUniformBuffer(uint32_t currentImage);

    void createDescriptorPool();

    void createImage(uint32_t width, uint32_t height, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage,
                     VkMemoryPropertyFlags properties, VkImage &image, VkDeviceMemory &imageMemory);

    void transitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout);

    void copyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height);

    void FrameRender(ImGui_ImplVulkanH_Window *wd, ImDrawData *draw_data);

    void FramePresent(ImGui_ImplVulkanH_Window *wd);

    void createIndexBuffer();

    void createUniformBuffers();

    void createAccelerationStructureBuffer(AccelerationStructure &accelerationStructure,
                                           VkAccelerationStructureBuildSizesInfoKHR buildSizeInfo);

    void deleteScratchBuffer(RayTracingScratchBuffer &scratchBuffer);

    VkCommandBuffer beginSingleTimeCommands();

    void endSingleTimeCommands(VkCommandBuffer commandBuffer);

    void createBottomLevelAccelerationStructure();

    /*
		The top level acceleration structure contains the scene's object instances
	*/
    void createTopLevelAccelerationStructure();

    VkResult createVksBuffer(VkBufferUsageFlags usageFlags, VkMemoryPropertyFlags memoryPropertyFlags,
                             vks::Buffer *buffer, VkDeviceSize size, void *data);

    RayTracingScratchBuffer createScratchBuffer(VkDeviceSize size);

    uint64_t getBufferDeviceAddress(VkBuffer buffer);

    uint32_t getMemoryType(VkPhysicalDevice physicalDevice, uint32_t typeFilter, VkMemoryPropertyFlags properties);

    void createStorageImage();

    void createUniformBuffer();

    void createShaderBindingTable();

    void createRayTracingPipeline();

    void setImageLayout(
        VkCommandBuffer cmdbuffer,
        VkImage image,
        VkImageLayout oldImageLayout,
        VkImageLayout newImageLayout,
        VkImageSubresourceRange subresourceRange);

    VkPipelineShaderStageCreateInfo loadShader(std::string fileName, VkShaderStageFlagBits stage);

    const int MAX_FRAMES_IN_FLIGHT = 2;
    const int minImages = 2;

    bool framebufferResized = false;
    bool isMinimized = false;

    vks::Buffer ubo;

    VkTransformMatrixKHR glmMat4ToVkTransformMatrixKHR(const glm::mat4& mat);

    struct UniformData {
        glm::mat4 viewInverse;
        glm::mat4 projInverse;
    } uniformData;
    
    const uint32_t WIDTH = 800;
    const uint32_t HEIGHT = 600;
    Model *model;
    VkBuffer vertexBuffer;
    vks::Buffer vertexBuffer2;
    vks::Buffer indexBuffer2;
    vks::Buffer unformBuffer2;
    VkDeviceMemory vertexBufferMemory;


    AccelerationStructure bottomLevelAS;
    AccelerationStructure topLevelAS{};

    VkBuffer lowASBuffer;
    VkDeviceMemory lowASBufferMemory;


    ImGuiIO io;
    const std::vector<const char *> validationLayers = {
        "VK_LAYER_KHRONOS_validation"
    };
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    ImGui_ImplVulkanH_Window imguiWindow;
    VkImage depthImage;
    VkDeviceMemory depthImageMemory;
    VkImageView depthImageView;

    VkImageView createImageView(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags);

    bool rasteryzation = true;
    
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
    VkDescriptorPool rayTracingDescriptorPool;
    std::vector<VkDescriptorSet> descriptorSets;
    std::vector<VkBuffer> uniformBuffers;
    std::vector<VkDeviceMemory> uniformBuffersMemory;
    std::vector<void *> uniformBuffersMapped;
    VkDescriptorSetLayout descriptorSetLayout;
    VkPipelineLayout pipelineLayout;
    uint32_t currentFrame = 0;
    uint32_t currentFrame2 = 0;
    std::vector<VkSemaphore> imageAvailableSemaphores;
    std::vector<VkSemaphore> renderFinishedSemaphores;
    std::vector<VkFence> inFlightFences;
    std::vector<VkSemaphore> imageAvailableSemaphores2;
    std::vector<VkSemaphore> renderFinishedSemaphores2;
    std::vector<VkFence> inFlightFences2;
    std::vector<VkCommandBuffer> commandBuffers;
    std::vector<VkCommandBuffer> drawCmdBuffers;
    VkCommandPool commandPool;
    VkCommandPool raytracingCommandPool;
    VkPipeline graphicsPipeline;
    VkRenderPass renderPass;
    VkRenderPass raytracingRenderPass;
    std::vector<VkFramebuffer> swapChainFramebuffers;
    std::vector<VkFramebuffer> raytracingSwapChainFramebuffers;
    std::vector<VkImageView> swapChainImageViews;
    VkFormat swapChainImageFormat;
    VkExtent2D swapChainExtent;
    VkExtent2D swapChainExtent2;
    std::vector<VkImage> swapChainImages;
    std::vector<VkImage> raycastSwapChainImages;
    VkSwapchainKHR swapChain;
    VkSwapchainKHR raycastingSwapChain;
    VkQueue presentQueue;
    VkQueue graphicsQueue;
    VkDevice device;
    VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
    SDL_Window *window;
    SDL_Window *window2;
    VkInstance instance;
    VkDebugUtilsMessengerEXT debugMessenger;
    VkSurfaceKHR surface;
    VkSurfaceKHR surface2;

    VkPipeline raytracingPipeline;
    VkPipelineLayout raytracingPipelineLayout;
    VkDescriptorSet raytracingDescriptorSet;
    VkDescriptorSetLayout raytracingDescriptorSetLayout;

    vks::Buffer raygenShaderBindingTable;
    vks::Buffer missShaderBindingTable;
    vks::Buffer hitShaderBindingTable;

    void createDescriptorSets2();

    VkCommandBuffer createCommandBuffer(VkCommandBufferLevel level);

    void flushCommandBuffer(VkCommandBuffer commandBuffer);

    void updateUniformBuffers();

    static uint32_t alignedSize(uint32_t value, uint32_t alignment);

    std::vector<VkRayTracingShaderGroupCreateInfoKHR> shaderGroups{};

    VkShaderModule toolLoadShader(const char *fileName, VkDevice device);

    VkWriteDescriptorSet writeDescriptorSet(
                VkDescriptorSet dstSet,
                VkDescriptorType type,
                uint32_t binding,
                VkDescriptorBufferInfo* bufferInfo,
                uint32_t descriptorCount = 1);

    VkWriteDescriptorSet writeDescriptorSet(
               VkDescriptorSet dstSet,
               VkDescriptorType type,
               uint32_t binding,
               VkDescriptorImageInfo *imageInfo,
               uint32_t descriptorCount = 1);

#ifdef DEBUG_BUILD
    const bool enableValidationLayers = true;
#else
    const bool enableValidationLayers = false;
#endif
};


#endif //VULKANMIRAGEPATHTRACER_H
