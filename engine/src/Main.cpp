#include <iostream>
#include <fstream>
#include <cmath>

#include <glad/glad.h>
#include <glm/glm.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

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

  std::vector<float> rotation = {
      0.5, 0, -0.9, 0,
      0, 1.0, 0, 0,
      0.9, 0, 0.5, 0,
      0, 0, 0, 1
  };

  std::vector<float> rotation2 = {
      1, 0, 0, 0,
      0, 0.5, -0.9, 0,
      0, 0.9, 0.5, 0,
      0, 0, 0, 1
  };

  std::vector<float> light = {1, 0, 0};

  std::vector<float> vertices = {
      // Top

      -0.5f, -0.5f, 0,
      -0.5, 0.5f, 0,
      0.5f, -0.5f, 0,

      -0.5f, 0.5f, 0,
      0.5f, 0.5f, 0,
      0.5f, -0.5f, 0,

    // Bottom

      -0.5f, -0.5f, -1,
      -0.5, 0.5f, -1,
      0.5f, -0.5f, -1,

      -0.5f, 0.5f, -1,
      0.5f, 0.5f, -1,
      0.5f, -0.5f, -1,

    // Front

      0.5f, -0.5f, 0,
      0.5f, 0.5f, 0,
      0.5f, -0.5f, -1,

      0.5f, 0.5f, 0,
      0.5f, 0.5f, -1,
      0.5f, -0.5f, -1,

    // Back

      -0.5f, -0.5f, 0,
      -0.5f, 0.5f, 0,
      -0.5f, -0.5f, -1,

      -0.5f, 0.5f, 0,
      -0.5f, 0.5f, -1,
      -0.5f, -0.5f, -1,

    // Left side

      -0.5f, 0.5f, 0,
      -0.5f, 0.5f, -1,
      0.5f, 0.5f, -1,

      -0.5f, 0.5f, 0,
      0.5f, 0.5f, -1,
      0.5f, 0.5f, 0,

    // Right side

      -0.5f, -0.5f, 0,
      -0.5f, -0.5f, -1,
      0.5f, -0.5f, -1,

      -0.5f, -0.5f, 0,
      0.5f, -0.5f, -1,
      0.5f, -0.5f, 0
  };

  std::vector<unsigned int> indices = {
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

  std::vector<float> tex_coords = {
    0.0f, 0.0,
    0.0f, 1.0,
    1.0f, 0.0,

    0.0f, 0.0,
    0.0f, 1.0,
    1.0f, 0.0,
    

    0.0f,0.0f,
    0.0f, 1.0f,
    1.0f, 0.0,

    0.0f, 0.0,
    0.0f, 1.0,
    1.0f, 0.0,
    
    0.0f, 0.0,
    0.0f, 1.0,
    1.0f, 0.0,

    0.0f, 0.0,
    0.0f, 1.0,
    1.0f, 0.0,
    
    0.0,0.0,
    0.0, 1.0,
    1.0, 0.0,

    0.0f, 0.0,
    0.0f, 1.0,
    1.0f, 0.0,

    0.0,0.0,
    0.0, 1.0,
    1.0, 0.0,

    0.0f, 0.0,
    0.0f, 1.0,
    1.0f, 0.0,

    0.0,0.0,
    0.0, 1.0,
    1.0, 0.0,

    0.0f, 0.0,
    0.0f, 1.0,
    1.0f, 0.0
   };



  // This part needs to be extracted later to a scene or whatever
  // -------------------------------------------------------------------------------------------------- //
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
  
  bufferSet.add(vertices, "aPos", 3);
  bufferSet.add(&indices);

  bufferSet.add(tex_coords,"tex_coords", 2);
  // -----------------------------------------------------------------------------------------------------//
  // Texture crap because we dont have a bind of textures

  glBindVertexArray(bufferSet.getId());

  for(Buffer b : bufferSet.buffers)
  {
      GLint location = glGetAttribLocation(bufferSet.program, b.shader_var.c_str());
      glEnableVertexAttribArray(location);
      glBindBuffer(GL_ARRAY_BUFFER, 0);
  }

  unsigned int TEX;
  glGenTextures(1, &TEX);

  stbi_set_flip_vertically_on_load(true); 
  int width, height, nrChannels;
  unsigned char *data = stbi_load("../texture.jpg", &width, &height, &nrChannels, 0); 
  if (data)
  {
          glBindTexture(GL_TEXTURE_2D, TEX);
          glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
          glGenerateMipmap(GL_TEXTURE_2D);
          glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT ); // for this tutorial: use GL_CLAMP_TO_EDGE to prevent semi-transparent borders. Due to interpolation it takes texels from next repeat 
          glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
          glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
          glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  }else{
      std::cout << "Failed to load texture" << std::endl;
  }   
  stbi_image_free(data);

  glBindVertexArray(0);
  // -----------------------------------------------------------------------------------------------------//
  bufferSet.add_uniform(&rotation, "rotation");
  bufferSet.add_uniform(&rotation2, "rotation2");
      
  // Material
  bufferSet.add_uniform(new glm::vec3({1.0f,0.5f,0.31f}),"material.ambient");
  bufferSet.add_uniform(new glm::vec3({1.0f,0.5f,0.31f}),"material.diffuse");
  bufferSet.add_uniform(new glm::vec3({0.5f,0.5f,0.5f}),"material.specular");
  bufferSet.add_uniform(new glm::vec1({32.0f}),"material.shininess");

  // Light
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