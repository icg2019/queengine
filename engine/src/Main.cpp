#include <iostream>
#include <fstream>
#include <cmath>

#include <glad/glad.h>
#include <glm/glm.hpp>


#define INCLUDE_SDL

#include "SDL_include.h"
#include "InputManager.h"
#include "Queengine.h"
#include "BufferSet.hpp"

#include "../include/log.h"

using namespace std;

unsigned int CompileShader(string filename, bool is_fragment);

int main(int argc, char **argv) {
  Queengine *engine = Queengine::GetInstance();

  float rotation[16] = {
      0.5, 0, -0.9, 0,
      0, 1.0, 0, 0,
      0.9, 0, 0.5, 0,
      0, 0, 0, 1
  };

  float rotation2[16] = {
      1, 0, 0, 0,
      0, 0.5, -0.9, 0,
      0, 0.9, 0.5, 0,
      0, 0, 0, 1
  };
  float light[3] = {1, 0, 0};
  float vertices[108] = {
    -0.5f, -0.5f, 0,
    -0.5, 0.5f, 0,
    0.5f, -0.5f, 0,

    -0.5f, 0.5f, 0,
    0.5f, 0.5f, 0,
    0.5f, -0.5f, 0,

    -0.5f, -0.5f, -1,
    -0.5, 0.5f, -1,
    0.5f, -0.5f, -1,

    -0.5f, 0.5f, -1,
    0.5f, 0.5f, -1,
    0.5f, -0.5f, -1,

    0.5f, -0.5f, 0,
    0.5f, 0.5f, 0,
    0.5f, -0.5f, -1,

    0.5f, 0.5f, 0,
    0.5f, 0.5f, -1,
    0.5f, -0.5f, -1,

    -0.5f, -0.5f, 0,
    -0.5f, 0.5f, 0,
    -0.5f, -0.5f, -1,

    -0.5f, 0.5f, 0,
    -0.5f, 0.5f, -1,
    -0.5f, -0.5f, -1,

    -0.5f, 0.5f, 0,
    -0.5f, 0.5f, -1,
    0.5f, 0.5f, -1,

    -0.5f, 0.5f, 0,
    0.5f, 0.5f, -1,
    0.5f, 0.5f, 0,

    -0.5f, -0.5f, 0,
    -0.5f, -0.5f, -1,
    0.5f, -0.5f, -1,

    -0.5f, -0.5f, 0,
    0.5f, -0.5f, -1,
    0.5f, -0.5f, 0
  };

  // std::vector<unsigned int> *indices = new std::vector<unsigned int>();
  unsigned int indices[36] = {
    0, 1, 2,
    3, 4, 5,
    6, 7, 8,
    9, 10, 11,
    12, 13, 14,
    15, 16, 17,
    18, 19, 20,
    21, 22, 23,
    24, 25, 26,
    27, 28, 29,
    30, 31, 32,
    33, 34, 35
  };

  std::vector<unsigned int> *p_indices = new std::vector<unsigned int>(indices, indices + sizeof(indices) / sizeof(unsigned int));
  std::vector<float> *p_vertices = new std::vector<float>(vertices, vertices + sizeof(vertices) / sizeof(float));
  std::vector<float> *p_light = new std::vector<float>(light, light + sizeof(light) / sizeof(float));
  std::vector<float> *p_rotation = new std::vector<float>(rotation, rotation + sizeof(rotation) / sizeof(float));
  std::vector<float> *p_rotation2 = new std::vector<float>(rotation2, rotation2 + sizeof(rotation2) / sizeof(float));

  float normal[108] = {
    0, 0, 1,
    0, 0, 1,
    0, 0, 1,

    0, 0, 1,
    0, 0, 1,
    0, 0, 1,

    0, 0, -1,
    0, 0, -1,
    0, 0, -1,

    0, 0, -1,
    0, 0, -1,
    0, 0, -1,

    1, 0, 0,
    1, 0, 0,
    1, 0, 0,

    1, 0, 0,
    1, 0, 0,
    1, 0, 0,

    -1, 0, 0,
    -1, 0, 0,
    -1, 0, 0,

    -1, 0, 0,
    -1, 0, 0,
    -1, 0, 0,

    0, 1, 0,
    0, 1, 0,
    0, 1, 0,

    0, 1, 0,
    0, 1, 0,
    0, 1, 0,

    0, -1, 0,
    0, -1, 0,
    0, -1, 0,

    0, -1, 0,
    0, -1, 0,
    0, -1, 0
  };

  // This part needs to be extracted later to a scene or whatever
  // -------------------------------------------------------------------------------------------------- //
  std::vector<glm::vec3> *data = new std::vector<glm::vec3>(); 

  data->push_back(glm::vec3(-0.5f, 0.0f, 0.0f));
  data->push_back(glm::vec3(0.0f, 0.75f, 0.0f));
  data->push_back(glm::vec3(0.5f, 0.0f, 0.0f));

  DEBUG("Vector size: " << data->data()->length());

  GLuint v_shader = CompileShader("vertex.glsl", false);
  GLuint f_shader = CompileShader("fragment.glsl", true);

  GLuint shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram,v_shader);
  glAttachShader(shaderProgram,f_shader);
  glLinkProgram(shaderProgram);
  glUseProgram(shaderProgram);

  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

  INFO("Initializing VAO");
  BufferSet bufferSet = BufferSet(shaderProgram);
  
  bufferSet.add(data, "aPos");
  bufferSet.add(p_indices, "");

  bufferSet.add_uniform(p_rotation, "rotation");
  bufferSet.add_uniform(p_rotation2, "rotation2");

      
  // Material
  bufferSet.add_uniform(new glm::vec3({1.0f,0.5f,0.31f}),"material.ambient");
  bufferSet.add_uniform(new glm::vec3({1.0f,0.5f,0.31f}),"material.diffuse");
  bufferSet.add_uniform(new glm::vec3({0.5f,0.5f,0.5f}),"material.specular");
  bufferSet.add_uniform(new glm::vec1({32.0f}),"material.shininess");

  bufferSet.add_uniform(new glm::vec3({1.2f, 1.0f, 2.0f}), "light.position");
  bufferSet.add_uniform(new glm::vec3({0.2f, 0.2f, 0.2f}), "light.ambient");
  bufferSet.add_uniform(new glm::vec3({0.5f, 0.5f, 0.5f}), "light.diffuse");
  bufferSet.add_uniform(new glm::vec3({1.0f, 1.0f, 1.0f}), "light.specular");

  glUseProgram(shaderProgram);
  // -------------------------------------------------------------------------------------------------- //

  engine->Run(bufferSet.getId());

  return 0;
}

unsigned int CompileShader(string filename, bool is_fragment) {
  filename = "engine/assets/shaders/" + filename;
  ifstream file(filename);
  string src = "";

  if(file.is_open()) {
    string line;
    while(getline(file, line)) src += line + "\n";
    file.close();
  } else {
    cout << "Could not load file [" << filename << "]" << endl;
    return 0;
  }

  unsigned int shader;
  if (is_fragment) {
    shader = glCreateShader(GL_FRAGMENT_SHADER);
  } else {
    shader = glCreateShader(GL_VERTEX_SHADER);
  }

  const char * src_str = src.c_str();
  glShaderSource(shader, 1, &src_str, NULL);
  glCompileShader(shader);

  int success;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    char log[512];
    glGetShaderInfoLog(shader, 512, NULL, log);
    cout << "Shader [" << filename << "] compilation failed: " << log << endl;
    return 0;
  }

  return shader;
}