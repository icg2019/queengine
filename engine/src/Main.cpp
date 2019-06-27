#include <iostream>
#include <glad/glad.h>
#include <fstream>
#include <cmath>
#include <thread>
#include <unistd.h>

#define INCLUDE_SDL

#include "SDL_include.h"
#include "InputManager.h"
#include "Queengine.h"

using namespace std;

int main(int argc, char **argv) {
  Queengine *engine = Queengine::GetInstance();

  // This part needs to be extracted later to a scene or whatever
  // -------------------------------------------------------------------------------------------------- //
  float object_vertices[] = {
    -0.25f, 0.0f,
    0.0f, 0.5f,
    0.25f, 0.0f,
  };

  unsigned int object_indices[] = {
    0, 1, 2,
  };

  vector<tuple<Shader, int>> shaders;

  Shader base_object_shader("engine/assets/shaders/vertex.glsl",
                            "engine/assets/shaders/base_fragment.glsl");
  base_object_shader.active = true;
  tuple<Shader, int> baseShader = make_tuple(base_object_shader, NULL);

  Shader first_object_shader("engine/assets/shaders/vertex.glsl",
                "engine/assets/shaders/fragment.glsl");
  first_object_shader.active = false;
  tuple<Shader, int> firstShader = make_tuple(first_object_shader, SDLK_1);

  Shader second_object_shader("engine/assets/shaders/vertex0.glsl",
                "engine/assets/shaders/fragment0.glsl");
  second_object_shader.active = false;
  tuple<Shader, int> secondShader = make_tuple(second_object_shader, SDLK_2);

  Shader third_object_shader("engine/assets/shaders/vertex1.glsl",
                "engine/assets/shaders/fragment0.glsl");
  third_object_shader.active = false;
  tuple<Shader, int> thirdShader = make_tuple(third_object_shader, SDLK_3);

  shaders.push_back(baseShader);
  shaders.push_back(firstShader);
  shaders.push_back(secondShader);
  shaders.push_back(thirdShader);

  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

  unsigned int VAO;
  unsigned int  VBO, EBO;
  glGenBuffers(1,&VBO);
  glGenBuffers(1,&EBO);
  glGenVertexArrays(1, &VAO);

  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

  glBufferData(GL_ARRAY_BUFFER, sizeof object_vertices , object_vertices, GL_STATIC_DRAW);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof object_indices, object_indices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 2, GL_FLOAT, GL_TRUE, 0, (void*)0);
  glEnableVertexAttribArray(0);

  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

  engine->Run(VAO, shaders);

  return 0;
}
