#define SDL_MAIN_HANDLED

#include <iostream>
#include <stdio.h>

#include "glm/glm.hpp"
#include <SDL.h>
#include "Test.hpp"
#include <OpenGL/gl3.h>

int main(int argcv, char ** argc) {
    // initialize all sdl components
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        printf("SDL_Init failed: %s\n", SDL_GetError());
        return -1;
    }
    // SDL_WINDOW_OPENGL means that we will be using this window for opengl. Returns null if error
    SDL_Window* window = SDL_CreateWindow("video editor", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 700, 600, SDL_WINDOW_OPENGL|SDL_WINDOW_RESIZABLE);
    
    if (window == NULL) {
        // In the case that the window could not be made...
        printf("Could not create window: %s\n", SDL_GetError());
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
    SDL_GLContext context = SDL_GL_CreateContext(window);
    
    if (context == NULL) {
        // In the case that the window could not be made...
        printf("Could not create context: %s\n", SDL_GetError());
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
    glClearColor(0.0f, 0.0f, 1.0f, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    SDL_GL_SwapWindow(window);
    
    // This makes our buffer swap syncronized with the monitor's vertical refresh
    SDL_GL_SetSwapInterval(1);
    
    bool loop = true;

    while(loop) {
        
        SDL_Event event;
        
        while(SDL_PollEvent(&event)) {
            
            switch(event.key.keysym.sym) {
                case SDLK_ESCAPE:
                    loop = false;
                    break;
                case SDLK_r:
                    glClearColor(1.0f, 0.0f, 0.0f, 1);
                    glClear(GL_COLOR_BUFFER_BIT);
                    SDL_GL_SwapWindow(window);
                    break;
                case SDLK_g:
                    glClearColor(0.0f, 1.0f, 0.0f, 1);
                    glClear(GL_COLOR_BUFFER_BIT);
                    SDL_GL_SwapWindow(window);
                    break;
                case SDLK_b:
                    glClearColor(0.0f, 0.0f, 1.0f, 1);
                    glClear(GL_COLOR_BUFFER_BIT);
                    SDL_GL_SwapWindow(window);
                    break;
                default:
                    break;
            }
        }
    }
    // Delete our OpengL context
    SDL_GL_DeleteContext(context);
    
    // Destroy our window
    SDL_DestroyWindow(window);
    
    // Shutdown SDL 2
    SDL_Quit();
}
