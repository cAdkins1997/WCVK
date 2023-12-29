cmake_minimum_required(VERSION 3.27)
project(OVKL)

set(CMAKE_CXX_STANDARD 17)

add_executable(OVKL main.cpp
        vulkan/VulkanCommon.h
        vulkan/Engine.cpp
        vulkan/Engine.h
        vulkan/Debug.cpp
        vulkan/Debug.h
        vulkan/Device.cpp
        vulkan/Device.h
        vulkan/Instance.cpp
        vulkan/Instance.h
)

find_package(Vulkan REQUIRED)
target_include_directories(${PROJECT_NAME} PUBLIC ${Vulkan_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} Vulkan::Vulkan)

add_subdirectory(include/glfw-3.3.8)
target_link_libraries(${PROJECT_NAME} glfw)