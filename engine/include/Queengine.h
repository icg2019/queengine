#ifndef QUEENGINE_H
#define QUEENGINE_H
#define INCLUDE_SDL

#include <iostream>
#include <glad/glad.h>
#include <fstream>
#include <cmath>

#include "InputManager.h"
#include "SDL_include.h"
#include "Shader.h"
#include "Texture.h"
#include "TextureLoader.h"
#include <vector>
#include <tuple>

#include "log.h"

class Queengine {
  private:
    SDL_GLContext context;
    SDL_Window *window;
    static Queengine *instance;
    Queengine();

  public:
    ~Queengine();
    void Run(unsigned int VAO, int indices);
    void Run(unsigned int VAO, vector<tuple<Shader, int>> shaderList, vector<tuple<Texture, int, int>> textures);
    void Run(unsigned int VAO, int number_of_triangles, vector<tuple<Shader, int>> shaderList, vector<tuple<Texture, int, int>> textures);
    static Queengine *GetInstance();
    void Run(GLuint VAO);
};

#endif
