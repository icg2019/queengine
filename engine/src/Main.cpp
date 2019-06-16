#include <iostream>
#include <glad/glad.h>
#include <fstream>
#include <cmath>

#define INCLUDE_SDL

#include "SDL_include.h"
#include "InputManager.h"
#include "Queengine.h"

using namespace std;

int main(int argc, char **argv) {
  Queengine *engine = Queengine::GetInstance();

  // This part needs to be extracted later to a scene or whatever
  // -------------------------------------------------------------------------------------------------- //
  float vertices[] = {
    -0.5f, 0.0f,
    0.0f, 0.75f,
    0.5f, 0.0f
  };

  unsigned int indices[] = {
    0, 1, 2
  };

  Shader shader("engine/assets/shaders/vertex.glsl",
                "engine/assets/shaders/fragment.glsl");
  shader.Use();

  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

  unsigned int VAO;
  unsigned int  VBO, EBO;
  glGenBuffers(1,&VBO);
  glGenBuffers(1,&EBO);
  glGenVertexArrays(1, &VAO);

  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof vertices , vertices, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof indices, indices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 2, GL_FLOAT, GL_TRUE, 0, (void*)0);
  glEnableVertexAttribArray(0);

  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

  shader.Use();
  // -------------------------------------------------------------------------------------------------- //

  engine->Run(VAO, &shader);

  return 0;
}
