
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

#include "Device.h"
#include "Instance.h"

using namespace renderer;

const uint32_t WIDTH = 1920;
const uint32_t HEIGHT = 1080;

const int MAX_FRAMES_IN_FLIGHT = 2;

class Engine {

public:
    Engine() = default;

    void mainLoop() {
        while (!glfwWindowShouldClose(instance.window)) {
            glfwPollEvents();
            drawFrame();
        }

        vkDeviceWaitIdle(VkDevice(device));
    }

    void run() {
        instance.createWindow();
        vk_init();
        mainLoop();
        cleanUp();
    }

    void vk_init();
    void cleanUp();

    VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
    VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
    VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);
    void createSwapChain();
    void createImageViews();

    static std::vector<char> readFile(const std::string& filename);
    void createGraphicsPipeline();
    VkShaderModule createShaderModule(const std::vector<char>& code);
    bool loadShaderModule(const char* filePath, VkShaderModule* outShaderModule);

    void createCommandPool();
    void createCommandBuffers();
    void recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);

    void createSyncObjects();

    void drawFrame();

    void createFramebuffers();
    static void framebufferResizeCallback(GLFWwindow* window, int width, int height);
    void recreateSwapChain();
    void cleanUpSwapChain();
    void createRenderPass();

    [[nodiscard]] GLFWwindow *getWindow() const { return instance.window; }


public:

    Instance instance;
    Device device;

    VkCommandPool commandPool;
    std::vector<VkCommandBuffer> commandBuffers;

    VkQueue presentQueue;

    VkSwapchainKHR swapChain;
    std::vector<VkImage> swapChainImages;
    VkFormat swapChainImageFormat;
    VkExtent2D swapChainExtent;
    std::vector<VkImageView> swapChainImageViews;
    std::vector<VkFramebuffer> swapChainFramebuffers;

    VkPipeline graphicsPipeline;
    VkPipelineLayout pipelineLayout;
    VkRenderPass renderPass;

    std::vector<VkSemaphore> imageAvailableSemaphores;
    std::vector<VkSemaphore> renderFinishedSemaphores;
    std::vector<VkFence> inFlightFences;

    VkDebugUtilsMessengerEXT debugMessenger;

    uint32_t currentFrame = 0;
    bool framebufferResized = false;
};


#endif //OVKL_ENGINE_H
