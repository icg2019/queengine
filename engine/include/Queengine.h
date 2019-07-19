#ifndef QUEENGINE_H
#define QUEENGINE_H
#define INCLUDE_SDL

#include <cmath>
#include <fstream>
#include <glad/glad.h>
#include <iostream>

#include "InputManager.h"
#include "Rect.h"
#include "SDL_include.h"
#include "Shader.h"
// #include "Texture.h"
#include "TextureLoader.h"
#include <tuple>
#include <vector>

#include "Circle.hpp"
#include "GameObject.hpp"
#include "log.h"

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
  void HandleInput(vector<Shader> &, vector<tuple<TextureLoader, int, int>>);
  Rect GetGLCanvasArea();
  void Run(unsigned int VAO, vector<Shader> shaderList,
           vector<tuple<TextureLoader, int, int>> textures);
  void Run(vector<Shader> &shaderList,
           vector<tuple<TextureLoader, int, int>> textures);
  static Queengine *GetInstance();
  void Run(GLuint VAO);
  vector<GameObject *> primitives;
};

#endif
