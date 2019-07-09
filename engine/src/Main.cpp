#include <iostream>
#include <fstream>
#include <cmath>
#include <algorithm>
#include <functional>

#include <glad/glad.h>
#include <glm/glm.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#define INCLUDE_SDL

#include "SDL_include.h"
#include "InputManager.h"
#include "Queengine.h"
#include "BufferSet.hpp"
#include "Triangle.hpp"
#include "Rectangle.hpp"
#include "Circle.hpp"

#include "../include/log.h"

using namespace std;

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
  vector<glm::vec3> my_coordinates = {
		glm::vec3(-0.5, 0.5, 0.0),
		glm::vec3(0.5, 0.5, 0.0),
		glm::vec3(-0.5, -0.5, 0.0),
    glm::vec3(0.5, -0.5, 0.0),
	};

  Circle circle1 = Circle({0.0, 0.0, 0.0}, 0.5, 100);
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

  // float* vertices = triangle1.get_coordinates();
  float* vertices = circle1.get_coordinates();
  // float* vertices = rectangle1.get_coordinates();

  // unsigned int indices[] = {
  //   0, 1, 2
  // };

  // unsigned int* indices = triangle1.get_indices();
  unsigned int* indices = circle1.get_indices();
  // unsigned int* indices = rectangle1.get_indices();

  // int coordinates_size = triangle1.get_coordinates_size();
  // int indices_size = triangle1.get_indices_size();

  int coordinates_size = circle1.get_coordinates_size();
  int indices_size = circle1.get_indices_size();

  // int coordinates_size = rectangle1.get_coordinates_size();
  // int indices_size = rectangle1.get_indices_size();

  vector<tuple<Shader, int>> shaders;

  Shader base_object_shader("engine/assets/shaders/vertex.glsl",
                            "engine/assets/shaders/base_fragment.glsl");
  base_object_shader.active = true;
  tuple<Shader, int> baseShader = make_tuple(base_object_shader, NULL);

  Shader first_object_shader("engine/assets/shaders/vertex.glsl",
                "engine/assets/shaders/fragment.glsl");
  first_object_shader.active = false;
  tuple<Shader, int> firstShader = make_tuple(first_object_shader, SDLK_1);

  Shader second_object_shader("engine/assets/shaders/vertex.glsl",
                "engine/assets/shaders/fragment0.glsl");
  second_object_shader.active = false;
  tuple<Shader, int> secondShader = make_tuple(second_object_shader, SDLK_2);

  shaders.push_back(baseShader);
  shaders.push_back(firstShader);
  shaders.push_back(secondShader);

  vector<tuple<Texture, int, int> > textures;

  Texture texture1("engine/assets/textures/laranjo.png");
  tuple<Texture, int, int> firstTexture = make_tuple(texture1, 0, GL_TEXTURE0);

  Texture texture2("engine/assets/textures/lua.png");
  tuple<Texture, int, int> secondTexture = make_tuple(texture2, 1, GL_TEXTURE1);

  Texture texture3("engine/assets/textures/chao.jpg");
  tuple<Texture, int, int> thirdTexture = make_tuple(texture3, 2, GL_TEXTURE2);

  Texture texture4("engine/assets/textures/muro.jpg");
  tuple<Texture, int, int> forthyTexture = make_tuple(texture4, 3, GL_TEXTURE3);

  textures.push_back(firstTexture);
  textures.push_back(secondTexture);
  textures.push_back(thirdTexture);
  textures.push_back(forthyTexture);

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

  engine->Run(VAO, indices_size/sizeof(unsigned int), shaders, textures);
  // std::vector<float> vertices2 = vertices;

  // std::transform(vertices2.begin(), vertices2.end(), vertices2.begin(),
  //              std::bind(std::multiplies<float>(), std::placeholders::_1, 3));


  // bufferSet.resize(&vertices2, "aPos");

  engine->Run(bufferSet.getId());

  return 0;
}
