#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <SDL.h>
#include <string>

class Window {
public:
    Window();
    ~Window();
    int create(std::string name, int w, int h, unsigned int flags);
    void swapWindow();
    void printSDL_GL_Attributes();
private:
    SDL_Window* _window;
    SDL_GLContext _context;
};

#endif // WINDOW_HPP
