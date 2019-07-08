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
#include "Triangle.hpp"
#include "Circle.hpp"
#include "Rectangle.hpp"

using namespace std;

int main(int argc, char **argv) {
  Queengine *engine = Queengine::GetInstance();

  // This part needs to be extracted later to a scene or whatever
  // -------------------------------------------------------------------------------------------------- //
//   vector<glm::vec3> my_coordinates = {
//	 	glm::vec3(-0.5, 0.0, 0.0),
//	 	glm::vec3(0.0, 0.75, 0.0),
//	 	glm::vec3(0.5, 0.0, 0.0),
//	 };
//
//   std::vector<glm::vec1> my_indices = {
//	 	glm::vec1(0.0),
//	 	glm::vec1(1.0),
//	 	glm::vec1(2.0),
//	 };

  vector<glm::vec3> my_coordinates = {
		glm::vec3(-0.5, 0.5, 0.0),
		glm::vec3(0.5, 0.5, 0.0),
		glm::vec3(-0.5, -0.5, 0.0),
    glm::vec3(0.5, -0.5, 0.0),
	};

  // Triangle triangle1 = Triangle(my_coordinates, my_indices);
  // Circle circle1 = Circle();
  Circle circle1 = Circle({0.0, 0.0, 0.0}, 0.5, 100);
  // Rectangle rectangle1 = Rectangle(my_coordinates);

  // float vertices[] = {
  //   -0.5f, 0.0f,
  //   0.0f, 0.75f,
  //   0.5f, 0.0f
  // };

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

  unsigned int VBO;
  glGenBuffers(1, &VBO);

  unsigned int NBO;
  glGenBuffers(1, &NBO);

  unsigned int TBO;
  glGenBuffers(1, &TBO);
  unsigned int EBO;
  glGenBuffers(1, &EBO);

  unsigned int VAO;
  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, coordinates_size, vertices, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_size, indices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, 0, (void*)0);
  glEnableVertexAttribArray(0);

  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

  // -------------------------------------------------------------------------------------------------- //

  engine->Run(VAO, indices_size/sizeof(unsigned int), shaders, textures);

  return 0;
}
