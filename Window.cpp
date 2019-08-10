#include "Window.hpp"
#include <iostream>

#ifdef __APPLE__
#include <OpenGL/gl3.h>
#else // !__APPLE__
#ifdef _WIN32
#include <Windows.h>
#endif // _WIN32
#ifndef _GL_H
#include <GL/glew.h>
#endif // _GL_H
#include <GL/gl.h>
#include <GL/glu.h>
#endif // __APPLE__

Window::Window() : _window(nullptr), _context(nullptr) {}

int Window::create(std::string name, int w, int h, unsigned int flags) {
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        std::cerr << "SDL_Init failed: " << SDL_GetError() << std::endl;
        return 1;
    }
    // SDL_WINDOW_OPENGL means that we will be using this window for opengl. Returns null if error
    _window = SDL_CreateWindow("video editor", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, flags);
    
    if (_window == NULL) {
        // In the case that the window could not be made...
        std::cerr << "Could not create window: " << SDL_GetError() << std::endl;
        return 1;
    }
    
    // SDL_GL_CONTEXT_CORE gives us only the newer version, deprecated functions are disabled
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    // set the opengl context version
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    // turn on double buffering, meaning that everything is drawn on a back buffer and then swapped with the front buffer when ready. This makes things appear smoother
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    
    // A process can create multiple OpenGL contexts. Each context can represent a separate viewable surface, like a window in an application
    _context = SDL_GL_CreateContext(_window);
    
    if (_context == NULL) {
        // In the case that the window could not be made...
        std::cerr << "Could not create context: " << SDL_GetError() << std::endl;
        return 1;
    }
    
#ifdef __APPLE__
    // creating vertex array object and setting it as the current one
    GLuint vertexArrayID;
    glGenVertexArrays(1, &vertexArrayID);
    glBindVertexArray(vertexArrayID);
#elif defined(__GLEW_H__)
    //Set up glew (recommended for windows)
    glewExperimental = GL_TRUE;
    GLenum error = glewInit();
    if (error != GLEW_OK) {
        return COULD_NOT_INIT_GLEW;
    }
#endif
    // set the color to use when clearing the screen
    glClearColor(0.0f, 0.0f, 0.0f, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    SDL_GL_SwapWindow(_window);
    
    // This makes our buffer swap syncronized with the monitor's vertical refresh
    SDL_GL_SetSwapInterval(1);
    
    return 0;
}

void Window::swapWindow() {
    SDL_GL_SwapWindow(_window);
}

void Window::printSDL_GL_Attributes()
{
    int value = 0;
    SDL_GL_GetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, &value);
    std::cout << "SDL_GL_CONTEXT_MAJOR_VERSION : " << value << std::endl;
    
    SDL_GL_GetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, &value);
    std::cout << "SDL_GL_CONTEXT_MINOR_VERSION: " << value << std::endl;
}


Window::~Window() {
    // Delete our OpengL context
    SDL_GL_DeleteContext(_context);
    
    // Destroy our window
    SDL_DestroyWindow(_window);
    
    // Shutdown SDL 2
    SDL_Quit();
}
