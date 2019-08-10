#define SDL_MAIN_HANDLED

#include <iostream>
#include <stdio.h>

#include "glm/glm.hpp"
#include <SDL.h>
#include "Window.hpp"

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

int main(int argcv, char ** argc) {
    Window window = Window();
    window.create("test", 700, 600, SDL_WINDOW_OPENGL|SDL_WINDOW_RESIZABLE);
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
                    window.swapWindow();
                    break;
                case SDLK_g:
                    glClearColor(0.0f, 1.0f, 0.0f, 1);
                    glClear(GL_COLOR_BUFFER_BIT);
                    window.swapWindow();
                    break;
                case SDLK_b:
                    glClearColor(0.0f, 0.0f, 1.0f, 1);
                    glClear(GL_COLOR_BUFFER_BIT);
                    window.swapWindow();
                    break;
                default:
                    break;
            }
        }
    }
}
