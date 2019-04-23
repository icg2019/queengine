#ifndef QUEENGINE_H
#define QUEENGINE_H
#define INCLUDE_SDL

#include "SDL_include.h"

class Queengine {
  private:
    SDL_GLContext context;
    SDL_Window *window;
    static Queengine *instance;
    Queengine();

  public:
    ~Queengine();
    Queengine *GetInstance(); 
};

#endif