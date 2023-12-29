
#ifndef OVKL_DEVICE_H
#define OVKL_DEVICE_H

#include <optional>
#include <set>

#include "Debug.h"

namespace renderer {

    const std::vector<const char*> deviceExtensions = {
            VK_KHR_SWAPCHAIN_EXTENSION_NAME
    };

    struct QueueFamilyIndices {
        std::optional<uint32_t> graphicsFamily;
        std::optional<uint32_t> presentFamily;
        std::optional<uint32_t> computeFamily;
        std::optional<uint32_t> transferFamily;

        [[nodiscard]] bool isComplete() const {
            return graphicsFamily.has_value();
        }
    };

    struct SwapChainSupportDetails {
        VkSurfaceCapabilitiesKHR capabilities;
        std::vector<VkSurfaceFormatKHR> formats;
        std::vector<VkPresentModeKHR> presentModes;
    };

    struct Device {
        Device() = default;
        ~Device();

        void choosePhysicalDevice(VkInstance instance, VkSurfaceKHR surface);
        QueueFamilyIndices findQueueFamilies(VkPhysicalDevice& device, VkSurfaceKHR surface);
        SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device, VkSurfaceKHR surface);
        bool checkDeviceExtensionSupport(VkPhysicalDevice device);
        void createLogicalDevice(VkSurfaceKHR surface);
        [[nodiscard]] VkFormat getSupportedDepthFormat(bool checkSamplingSupport) const;

        VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
        VkDevice logicalDevice = VK_NULL_HANDLE;
        VkQueue graphicsQueue = VK_NULL_HANDLE;
        VkQueue presentQueue = VK_NULL_HANDLE;
        VkQueue computeQueue = VK_NULL_HANDLE;
        VkCommandPool commandPool = VK_NULL_HANDLE;
        bool isDeviceSuitable(VkPhysicalDevice device, VkSurfaceKHR surface);

        explicit operator VkDevice() const {
            return logicalDevice;
        };

        explicit operator VkPhysicalDevice() const {
            return physicalDevice;
        }
    };
}


#endif //OVKL_DEVICE_H
