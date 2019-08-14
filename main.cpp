#define GLFW_INCLUDE_VULKAN
// with GLFW_INCLUDE_VULKAN defined this will load vulkan.h with glfw
#include <GLFW/glfw3.h>

// math library for linear algebra
#include "glm/glm.hpp"

#include <iostream>
// report errors by catching exceptions
#include <stdexcept>
// functional headers will be used by lambda function in resource management
#include <functional>
// cstdlib header provides access to the EXIT_SUCCESS and EXIT_FAILURE macros
#include <cstdlib>
#include <vector>
#include <string>

class Application {
public:
    void run() {
        initWindow();
        initVulkan();
        mainLoop();
        cleanUp();
    }
private:
    GLFWwindow* _window;
    VkInstance _instance;
    const int _WIDTH = 800;
    const int _HEIGHT = 600;
    
    const std::vector<const char*> _validationLayers = {
        "VK_LAYER_KHRONOS_validation"
    };
    
#ifdef NDEBUG
    const bool _enableValidationLayers = false;
#else
    const bool _enableValidationLayers = true;
#endif
    
    void initWindow() {
        // initialize the GLFW libary
        glfwInit();
        // Because GLFW was originally designed to create an OpenGL context, we need to tell it to not create an OpenGL context with this hint
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        // resizing windows takes special care so we'll disable it for now
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

        // create the window. 4th param is optional to specify which monitor to open the window on. 5th param is only relevant to opengl
        _window = glfwCreateWindow(_WIDTH, _HEIGHT, "Vulkan Window", nullptr, nullptr);
    }
    void initVulkan() {
        // first thing to initialize vulkan library is by creating an instance which is the connection between your application and the Vulktan library
        createInstance();
    }
    void createInstance() {
        // if in debug mode check that all requested validation layers that we said we want in _validationLayers are available
        if(_enableValidationLayers) {
            checkValidationLayerSupport();
        }
        // fill in a struct with information about our application
        VkApplicationInfo appInfo = {};
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.apiVersion = VK_API_VERSION_1_0;
        appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.pApplicationName = "Application";
        appInfo.pEngineName = "No Engine";
        
        // Next struct tells the vulkan driver what global extensions and validation layers we want to use
        VkInstanceCreateInfo createInfo = {};
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pApplicationInfo = &appInfo;
        uint32_t glfwExtensionCount = 0;
        const char** glfwExtensions;
        glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
        createInfo.enabledExtensionCount = glfwExtensionCount;
        createInfo.ppEnabledExtensionNames = glfwExtensions;

        // if in debug mode set info to tell driver that we want to use validation layers
        if(_enableValidationLayers) {
            createInfo.enabledLayerCount = static_cast<uint32_t>(_validationLayers.size());
            createInfo.ppEnabledLayerNames = _validationLayers.data();
        } else {
            createInfo.enabledLayerCount = 0;
        }
        
        uint32_t extensionCount = 0;
        // get number of supported extensions
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
        // allocate array to hold extension details
        std::vector<VkExtensionProperties> extensions(extensionCount);
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());
        // check that all required vulkan extensions by glfw are supported by this vulkan version. Throws an error otherwise
        checkRequiredExtensionsPresent(extensions, glfwExtensions, glfwExtensionCount);

        if(vkCreateInstance(&createInfo, nullptr, &_instance) != VK_SUCCESS) {
            throw std::runtime_error("failed to create instance!");
        }
    }
    // checks all @requiredExtCount required extensions @requiredExt are available @availableExt
    void checkRequiredExtensionsPresent(std::vector<VkExtensionProperties> availableExt, const char ** requiredExt, int requiredExtCount) {
        std::string unsupportedExt = "";
        for(int i = 0; i < requiredExtCount; ++i) {
            bool found = false;
            for(const VkExtensionProperties& ext : availableExt) {
                if(std::strcmp(requiredExt[i], ext.extensionName) == 0) {
                    found = true;
                    break;
                }
            }
            if(!found) {
                unsupportedExt += "\t" + std::string(requiredExt[i]) + "\n";
            }
        }
        if(!unsupportedExt.empty()) {
            throw std::runtime_error("unsupported vulkan extension(s):\n" + unsupportedExt);
        }
    }
    
    // checks if all required validation layers in _validationLayers is an available layer
    void checkValidationLayerSupport() {
        std::string unsupportedLayer = "";
        uint32_t layerCount;
        vkEnumerateInstanceLayerProperties(&layerCount, nullptr);
        std::vector<VkLayerProperties> availableLayers(layerCount);
        vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());
        
        for(const char* layerName : _validationLayers) {
            bool layerFound = false;
            for(const VkLayerProperties& layerProperties : availableLayers) {
                if(strcmp(layerName, layerProperties.layerName) == 0) {
                    layerFound = true;
                    break;
                }
            }
            if(!layerFound) {
                unsupportedLayer += "\t" + std::string(layerName) + "\n";
            }
        }
        if(!unsupportedLayer.empty()) {
            throw std::runtime_error("unsupported validation layer(s) requested:\n" + unsupportedLayer);
        }
    }
    
    void mainLoop() {
        // loops and checks weather the exit button has been pressed
        while(!glfwWindowShouldClose(_window)) {
            // processes all events currently in the event queue. Calls associated handlers
            glfwPollEvents();
        }
    }
    void cleanUp() {
        vkDestroyInstance(_instance, nullptr);
        
        // Destroys the specified window and its context
        glfwDestroyWindow(_window);

        // Destroys all remaining windows, cursors and other allocated resources
        glfwTerminate();
    }
};

int main(int argv, char ** argc) {
    Application app;
    try {
        app.run();
    } catch(const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}
