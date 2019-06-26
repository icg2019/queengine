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
  unsigned int NUMBER_OBJECTS = 2;

  vector<Shader> shaders;

  Shader base_object_shader("engine/assets/shaders/vertex.glsl",
                            "engine/assets/shaders/base_fragment.glsl");
  base_object_shader.active = true;

  Shader first_object_shader("engine/assets/shaders/vertex.glsl",
                "engine/assets/shaders/fragment.glsl");
  first_object_shader.active = false;
  // Shader second_object_shader("engine/assets/shaders/vertex0.glsl",
  //               "engine/assets/shaders/fragment0.glsl");
  // Shader third_object_shader("engine/assets/shaders/vertex1.glsl",
  //               "engine/assets/shaders/fragment0.glsl");

  shaders.push_back(base_object_shader);
  shaders.push_back(first_object_shader);
  // shaders.push_back(second_object_shader);
  // shaders.push_back(third_object_shader);

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

  float fobject_vertice[] = {
    object_vertices[0], object_vertices[1],
    object_vertices[2], object_vertices[3],
    object_vertices[4], object_vertices[5],
  };

  float sobject_vertice[] = {
    object_vertices[6], object_vertices[7],
    object_vertices[8], object_vertices[9],
    object_vertices[10], object_vertices[11],
  };

  unsigned int fobject_indice[] = {
    object_indices[0], object_indices[1], object_indices[2],
  };

  unsigned int sobject_indice[] = {
    object_indices[3], object_indices[4], object_indices[5],
  };

  // thread first_object_thread(&Queengine::Run, engine, fobject_vertice, fobject_indice, VAO, &first_object_shader);
  // first_object_thread.join();

  // thread second_object_thread(&Queengine::Run, engine, sobject_vertice, sobject_indice, VAO, &second_object_shader);
  // second_object_thread.join();
  engine->Run(VAO, shaders);

  return 0;
}
