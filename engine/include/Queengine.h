#ifndef QUEENGINE_H
#define QUEENGINE_H
#define INCLUDE_SDL

#include "SDL_include.h"
#include "Rect.h"

class Queengine {
  private:
    SDL_GLContext context;
    SDL_Window *window;
    Rect glCanvasArea;
    static Queengine *instance;
    Queengine();

  public:
    static Queengine *GetInstance();
    SDL_DisplayMode currentDisplay;
    ~Queengine();
    void Run(unsigned int VAO);
    void HandleInput();
    Rect GetGLCanvasArea();
};

#endif