#ifndef QUEENGINE_H
#define QUEENGINE_H
#define INCLUDE_SDL

#include <iostream>
#include <glad/glad.h>
#include <fstream>
#include <cmath>

#include "InputManager.h"
#include "SDL_include.h"

#include "log.h"

class Queengine {
  private:
    SDL_GLContext context;
    SDL_Window *window;
    static Queengine *instance;
    Queengine();

  public:
    ~Queengine();
    void Run(GLuint VAO);
    static Queengine *GetInstance(); 
};

#endif