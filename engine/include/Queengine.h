#ifndef QUEENGINE_H
#define QUEENGINE_H
#define INCLUDE_SDL

#include <iostream>
#include <glad/glad.h>
#include <fstream>
#include <cmath>

#include "InputManager.h"
#include "SDL_include.h"
#include "Rect.h"
#include "Shader.h"
// #include "Texture.h"
#include "TextureLoader.h"
#include <vector>
#include <tuple>

#include "log.h"
#include "GameObject.hpp"

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
    void HandleInput(vector<Shader> , vector<tuple<TextureLoader, int, int>>);
    Rect GetGLCanvasArea();
    void Run(unsigned int VAO, vector<Shader> shaderList, vector<tuple<TextureLoader, int, int>> textures);
    void Run(unsigned int VAO, int number_of_triangles, vector<Shader> shaderList, vector<tuple<TextureLoader, int, int>> textures);
    static Queengine *GetInstance();
    void Run(GLuint VAO);
    
    vector<GameObject> primitives;
};

#endif
