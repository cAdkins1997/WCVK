#include <iostream>

#include "Engine.h"

int main() {
    Engine engine;
    engine.vk_init();

    while (!glfwWindowShouldClose(engine.getWindow())) {
        glfwPollEvents();
    }

    engine.cleanUp();
}
