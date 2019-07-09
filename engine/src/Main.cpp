#include <iostream>
#include <fstream>
#include <cmath>
#include <algorithm>
#include <functional>

#include <glad/glad.h>
#include <glm/glm.hpp>

// #define STB_IMAGE_IMPLEMENTATION
// #include <stb_image.h>

#define INCLUDE_SDL

#include "SDL_include.h"
#include "InputManager.h"
#include "Texture.h"
#include "Queengine.h"
#include "BufferSet.hpp"
#include "Triangle.hpp"
#include "Rectangle.hpp"
#include "Circle.hpp"
#include "Shader.h"

#include "../include/log.h"

using namespace std;

int main(int argc, char **argv) {
  Queengine *engine = Queengine::GetInstance();

  // std::vector<float> rotation = {
  //     0.5, 0, -0.9, 0,
  //     0, 1.0, 0, 0,
  //     0.9, 0, 0.5, 0,
  //     0, 0, 0, 1
  // };

  // std::vector<float> rotation2 = {
  //     1, 0, 0, 0,
  //     0, 0.5, -0.9, 0,
  //     0, 0.9, 0.5, 0,
  //     0, 0, 0, 1
  // };
  
  vector<glm::vec3> my_coordinates = {
		glm::vec3(-0.5, 0.5, 0.0),
		glm::vec3(0.5, 0.5, 0.0),
		glm::vec3(-0.5, -0.5, 0.0),
    glm::vec3(0.5, -0.5, 0.0),
	};


  Shader first_object_shader("engine/assets/shaders/vertex_from_buffers.glsl",
                "engine/assets/shaders/fragment_from_buffers.glsl");

  Triangle primitiva = Triangle(first_object_shader);
  std::vector<float> light = {1, 0, 0};

  std::vector<float> vertices = primitiva.get_coordinates();


  std::vector<unsigned int> indices = primitiva.get_indices();


  std::vector<glm::vec2> tex_coords = primitiva.get_texture_coordinates();


  vector<tuple<Shader, int>> shaders;

  first_object_shader.active = false;
  tuple<Shader, int> firstShader = make_tuple(first_object_shader, SDLK_1);

  shaders.push_back(firstShader);
  

  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

  INFO("Initializing VAO");
  // -----------------------------------------------------------------------------------------------------//
  // Texture crap because we dont have a bind of textures

  BufferSet bufferSet = primitiva.get_buffer_set();

  // BufferSet bufferSet = BufferSet(first_object_shader.program_id);
  
  // bufferSet.add(vertices, "uPosition", 3);
  
  // bufferSet.add(&indices);

  // bufferSet.add(&tex_coords,"tex_coords");

  glBindVertexArray(bufferSet.getId());

  for(Buffer b : bufferSet.buffers)
  {
      GLint location = glGetAttribLocation(bufferSet.program, b.shader_var.c_str());
      glEnableVertexAttribArray(location);
      glBindBuffer(GL_ARRAY_BUFFER, 0);
  }

  vector<tuple<Texture, int, int> > textures;

  Texture texture1("../texture.jpg");
  tuple<Texture, int, int> firstTexture = make_tuple(texture1, 0, GL_TEXTURE0);

  
  textures.push_back(firstTexture);
  
  glBindVertexArray(0);
  



  //---------------------------------------
  // std::vector<float> vertices2 = vertices;

  // std::transform(vertices2.begin(), vertices2.end(), vertices2.begin(),
  //              std::bind(std::multiplies<float>(), std::placeholders::_1, 0.5));


  // bufferSet.resize(&vertices2, "uPosition");
//---------------------------------------
  engine->Run(bufferSet.getId(), primitiva.get_indices_size(), shaders, textures);


  return 0;
}
