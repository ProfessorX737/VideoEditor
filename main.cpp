#define GLFW_INCLUDE_VULKAN
// with GLFW_INCLUDE_VULKAN defined this will load vulkan.h with glfw
#include <GLFW/glfw3.h>

#include "glm/glm.hpp"

#include <iostream>

int main(int argcv, char ** argc) {
    // initialize the GLFW libary
    glfwInit();
    // Because GLFW was originally designed to create an OpenGL context, we need to tell it to not create an OpenGL context with this hint
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    // resizing windows takes special care so we'll disable it for now
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    
    // create the window. 4th param is optional to specify which monitor to open the window on. 5th param is only relevant to opengl
    GLFWwindow* window = glfwCreateWindow(800, 600, "Vulkan Window", nullptr, nullptr);
    
    uint32_t extensionCount = 0;
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

    std::cout << " extensions supported" << std::endl;
    
    // simple test to see if glm library is available 
    glm::mat4 matrix;
    glm::vec4 vec;
    auto test = matrix * vec;
    
    // loops and checks weather the exit button has been pressed
    while(!glfwWindowShouldClose(window)) {
        // processes all events currently in the event queue. Calls associated handlers
        glfwPollEvents();
    }
    
    // Destroys the specified window and its context
    glfwDestroyWindow(window);
    
    // Destroys all remaining windows, cursors and other allocated resources
    glfwTerminate();
}
