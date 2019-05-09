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
    SDL_DisplayMode currentDisplay;
    ~Queengine();
    void Run(unsigned int VAO);
    static Queengine *GetInstance();
    Rect GetGLCanvasArea();
};

#endif