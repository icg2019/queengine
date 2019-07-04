#include <iostream>
#include <glad/glad.h>
#include <fstream>
#include <cmath>

#define INCLUDE_SDL

#include "SDL_include.h"
#include "InputManager.h"
#include "Queengine.h"
#include "Triangle.hpp"

using namespace std;

unsigned int CompileShader(string filename, bool is_fragment);

void print_array(float* array, int size){
  for(int i = 0; i < size; i++){
    cout << array[i] << " ";
  }
  cout << endl;
}

void print_array2(unsigned int* array, int size){
  for(int i = 0; i < size; i++){
    cout << array[i] << " ";
  }
  cout << endl;
}

int main(int argc, char **argv) {
  Queengine *engine = Queengine::GetInstance();

  // This part needs to be extracted later to a scene or whatever
  // -------------------------------------------------------------------------------------------------- //
  Triangle triangle1 = Triangle();
  
  // float vertices[] = {
  //   -0.5f, 0.0f,
  //   0.0f, 0.75f,
  //   0.5f, 0.0f
  // };

  float* vertices = triangle1.get_coordinates();

  print_array(vertices, 6);

  // unsigned int indices[] = {
  //   0, 1, 2
  // };

  unsigned int* indices = triangle1.get_indices();

  print_array2(indices, 3);

  unsigned int v_shader = CompileShader("vertex.glsl", false);
  unsigned int f_shader = CompileShader("fragment.glsl", true);

  unsigned int  shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram,v_shader);
  glAttachShader(shaderProgram,f_shader);
  glLinkProgram(shaderProgram);
  glUseProgram(shaderProgram);

  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

  unsigned int VAO;
  unsigned int  VBO, EBO;
  glGenBuffers(1,&VBO);
  glGenBuffers(1,&EBO);
  glGenVertexArrays(1, &VAO);

  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, triangle1.get_coordinates_size() , vertices, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, triangle1.get_indices_size(), indices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 2, GL_FLOAT, GL_TRUE, 0, (void*)0);
  glEnableVertexAttribArray(0);

  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

  glUseProgram(shaderProgram);
  // -------------------------------------------------------------------------------------------------- //

  engine->Run(VAO);

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