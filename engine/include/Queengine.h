#ifndef QUEENGINE_H
#define QUEENGINE_H
#define INCLUDE_SDL

#include "SDL_include.h"
#include "Shader.h"
#include "ShaderObject.h"
#include <vector>

class Queengine {
  private:
    SDL_GLContext context;
    SDL_Window *window;
    static Queengine *instance;
    Queengine();

  public:
    ~Queengine();
    void Run(unsigned int VAO, vector<tuple<Shader, int>> shaderList);
    void Run(unsigned int VAO, int number_of_triangles, vector<tuple<Shader, int>> shaderList);
    static Queengine *GetInstance();
};

#endif
