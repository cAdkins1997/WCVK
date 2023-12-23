
#ifndef OVKL_VULKAN_APPLICATION_H
#define OVKL_VULKAN_APPLICATION_H

#include "common.h"

#endif //OVKL_VULKAN_APPLICATION_H

void cleanup(VkInstance instance, GLFWwindow* window) {
    vkDestroyInstance(instance, nullptr);
    glfwDestroyWindow(window);
    glfwTerminate();
}