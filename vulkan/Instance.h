
#ifndef OVKL_INSTANCE_H
#define OVKL_INSTANCE_H

#include "Debug.h"

using namespace renderer;

class Instance {

public:
    Instance() = default;
    ~Instance();

    void createInstance();
    void createWindow();
    void createSurface();

    explicit operator VkInstance() const {
        return instance;
    }

    explicit operator VkSurfaceKHR() const {
        return surface;
    }

    int width = 1920, height = 1080;
    VkInstance instance = VK_NULL_HANDLE;
    GLFWwindow* window;
    VkSurfaceKHR surface;
};


#endif //OVKL_INSTANCE_H
