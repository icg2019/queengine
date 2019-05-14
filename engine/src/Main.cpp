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

using namespace std;

unsigned int CompileShader(string filename, bool is_fragment);

int main(int argc, char **argv) {
  Queengine *engine = Queengine::GetInstance();

  // This part needs to be extracted later to a scene or whatever
  // -------------------------------------------------------------------------------------------------- //
  glm::vec3* data = (glm::vec3*) malloc(3*sizeof(glm::vec3));
  
  data[0] = glm::vec3(-0.5f, 0.0f, 0.0f);
  data[1] = glm::vec3(0.0f, 0.75f, 0.0f);
  data[2] = glm::vec3(0.5f, 0.0f, 0.0f);

  // float vertices[] = {
  //   -0.5f, 0.0f,
  //   0.0f, 0.75f,
  //   0.5f, 0.0f
  // };

  glm::vec1* indices = (glm::vec1*) malloc(3*sizeof(glm::vec1));

  indices[0] = glm::vec1(0.0f);
  indices[0] = glm::vec1(1.0f);
  indices[0] = glm::vec1(2.0f);

  // unsigned int indices[] = {
  //   0, 1, 2
  // };

  GLuint v_shader = CompileShader("vertex.glsl", false);
  GLuint f_shader = CompileShader("fragment.glsl", true);

  GLuint shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram,v_shader);
  glAttachShader(shaderProgram,f_shader);
  glLinkProgram(shaderProgram);
  glUseProgram(shaderProgram);

  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

  BufferSet bufferSet = BufferSet(shaderProgram);
  
  bufferSet.add(data, "aPos");
  bufferSet.add(indices, "");

  // unsigned int VAO;
  // unsigned int  VBO, EBO;
  // glGenBuffers(1,&VBO);
  // glGenBuffers(1,&EBO);
  // glGenVertexArrays(1, &VAO);



  // glBindVertexArray(VAO);

  // glBindBuffer(GL_ARRAY_BUFFER, VBO);
  // glBufferData(GL_ARRAY_BUFFER, sizeof vertices , vertices, GL_STATIC_DRAW);

  // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof indices, indices, GL_STATIC_DRAW);

  // glVertexAttribPointer(0, 2, GL_FLOAT, GL_TRUE, 0, (void*)0);
  // glEnableVertexAttribArray(0);

  // glBindVertexArray(0);
  // glBindBuffer(GL_ARRAY_BUFFER, 0);
  // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

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