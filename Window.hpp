#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <SDL.h>

class Window {
public:

private:
    SDL_Window* _window;
    SDL_GLContext _glContext;
    int _screenWidth;
    int _screenHeight;
}

#endif // WINDOW_HPP