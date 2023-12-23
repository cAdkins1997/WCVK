
#ifndef OVKL_ENGINE_H
#define OVKL_ENGINE_H

#include <vector>
#include <stdexcept>
#include <iostream>
#include <map>
#include <optional>
#include <cstring>
#include <set>
#include <limits>
#include <algorithm>
#include <fstream>

#include "common.h"
#include "Pipeline.h"

const std::vector<const char*> validationLayers = {
        "VK_LAYER_KHRONOS_validation"
};

const std::vector<const char*> deviceExtensions = {
        VK_KHR_SWAPCHAIN_EXTENSION_NAME
};

#ifdef NDEBUG
const bool enableValidationLayers = false;
#else
const bool enableValidationLayers = true;
#endif

struct QueueFamilyIndices {
    std::optional<uint32_t> graphicsFamily;
    std::optional<uint32_t> presentFamily;

    [[nodiscard]] bool isComplete() const {
        return graphicsFamily.has_value();
    }
};

struct SwapChainSupportDetails {
    VkSurfaceCapabilitiesKHR capabilities;
    std::vector<VkSurfaceFormatKHR> formats;
    std::vector<VkPresentModeKHR> presentModes;
};

VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
                                      const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger);
void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator);

class Engine {

public:
    Engine() {
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
        window = glfwCreateWindow(1920, 1080, "OVKL", nullptr, nullptr);
    }

    void vk_init();
    void cleanUp();

    bool checkValidationLayerSupport();
    void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
    void setupDebugMessenger();
    std::vector<const char*> getRequiredExtensions();
    static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
                                                        VkDebugUtilsMessageTypeFlagsEXT messageType,
                                                        const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData);


    void createInstance();

    void choosePhysicalDevice();
    bool isDeviceSuitable(VkPhysicalDevice device);
    QueueFamilyIndices findQueueFamilies(VkPhysicalDevice& device);

    void createLogicalDevice();
    std::vector<VkDeviceQueueCreateInfo> createQueueInfo(QueueFamilyIndices& indices);
    bool checkDeviceExtensionSupport(VkPhysicalDevice device);

    VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
    VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
    VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);
    SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);
    void createSwapChain();
    void createSurface();
    void createImageViews();

    void initializePipelines();
    VkPipelineLayoutCreateInfo pipelineLayoutCreateInfo();

    void initCommandPools();

    [[nodiscard]] GLFWwindow *getWindow() const {
        return window;
    }

    [[nodiscard]] const VkInstance_T *getInstance() const {
        return instance;
    }

private:
    uint32_t windowWidth, windowHeight;

    GLFWwindow* window;

    VkInstance instance;
    VkDebugUtilsMessengerEXT debugMessenger;

    VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;

    VkDevice logicalDevice = VK_NULL_HANDLE;
    VkQueue graphicsQueue = VK_NULL_HANDLE;

    VkCommandPool commandPool;
    VkCommandBuffer mainCommandBuffer;

    VkSurfaceKHR surface;
    VkQueue presentQueue;

    VkSwapchainKHR swapChain;
    VkExtent2D swapChainExtent;
    VkFormat swapchainImageFormat;
    std::vector<VkImage> swapChainImages;
    std::vector<VkImageView> swapchainImageViews;

    VkPipelineLayout trianglePipelineLayout;

    bool loadShaderModule(const char* filePath, VkShaderModule* outShaderModule);
};


#endif //OVKL_ENGINE_H
