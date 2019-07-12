#include "../include/Rectangle.hpp"
#include <set>

Rectangle::Rectangle(Shader shader) : bufferSet(shader.program_id) {

  vector<glm::vec3> coordinates = {
      glm::vec3(-0.5, 0.5, 0.0), glm::vec3(0.5, 0.5, 0.0),
      glm::vec3(0.5, -0.5, 0.0), glm::vec3(-0.5, -0.5, 0.0),
  };

  // Criar metodo para Verificar se o caminho da textura esta certo
  std::string texture_path = "../assets/pixes.bmp";

  std::vector<glm::vec1> indices = {glm::vec1(0.0), glm::vec1(1.0),
                                    glm::vec1(2.0), glm::vec1(0.0),
                                    glm::vec1(2.0), glm::vec1(3.0)};

  this->coordinates = coordinates;
  this->texture_path = texture_path;
  this->indices = indices;

  this->texture_coordinates = std::vector<glm::vec2>(4);
  this->texture_coordinates[0] = glm::vec2(-0.5, 0.5);
  this->texture_coordinates[2] = glm::vec2(0.5, 0.5);
  this->texture_coordinates[1] = glm::vec2(0.5, -0.5);
  this->texture_coordinates[3] = glm::vec2(-0.5, -0.5);

  std::vector<glm::vec3> vertices_tmp = this->get_coordinates();
  std::vector<unsigned int> indices_temp = this->get_indices();
  std::vector<glm::vec2> tex_coords = this->get_texture_coordinates();

  this->bufferSet.add(&vertices_tmp, "uPosition");
  this->bufferSet.add(&indices_temp);
  this->bufferSet.add(&tex_coords, "tex_coords");
}

std::vector<glm::vec3> Rectangle::get_coordinates() {
  return this->coordinates;
}

unsigned int Rectangle::get_coordinates_size() {
  return this->coordinates.size() * 3 * sizeof(float);
}

void Rectangle::set_coordinates(std::vector<glm::vec3> coordinates) {
  this->coordinates = coordinates;
  this->bufferSet.add(&this->coordinates, "uPosition");
}

std::vector<glm::vec2> Rectangle::get_texture_coordinates() {
  return this->texture_coordinates;
}

int Rectangle::get_vertice(glm::vec3 mouse_position) {
  const double radius = 0.1;
  for (int i = 0; i < this->coordinates.size(); i++) {
    double dist = hypot(this->coordinates[i].x - mouse_position.x,
                        this->coordinates[i].y - mouse_position.y);
    if (dist < radius)
      return i;
  }
  return -1;
}

double area_rec(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3) {
  return abs(
      (p1.x * (p2.y - p3.y) + p2.x * (p3.y - p1.y) + p3.x * (p1.y - p2.y)) /
      2.0);
}

bool Rectangle::point_is_inside(glm::vec3 mouse_position) {
  double a = area_rec(this->coordinates[0], this->coordinates[1],
                      this->coordinates[2]) +
             area_rec(this->coordinates[0], this->coordinates[3],
                      this->coordinates[2]);

  double a1 =
      area_rec(mouse_position, this->coordinates[0], this->coordinates[1]);
  double a2 =
      area_rec(mouse_position, this->coordinates[1], this->coordinates[2]);
  double a3 =
      area_rec(mouse_position, this->coordinates[2], this->coordinates[3]);
  double a4 =
      area_rec(mouse_position, this->coordinates[0], this->coordinates[3]);

  return (a == a1 + a2 + a3 + a4);
}

void Rectangle::set_texture_coordinates(
    std::vector<glm::vec2> texture_coordinates) {
  this->texture_coordinates = texture_coordinates;
}

std::string Rectangle::get_texture_path() { return this->texture_path; }

void Rectangle::set_texture_path(const std::string &texture_path) {
  this->texture_path = texture_path;
}

std::vector<unsigned int> Rectangle::get_indices() {
  std::vector<unsigned int> indices_array =
      std::vector<unsigned int>(this->indices.size());

  for (int i = 0; i < this->indices.size(); i++) {
    indices_array[i] = this->indices[i].x;
  }

  return indices_array;
}

unsigned int Rectangle::get_indices_size() {
  return this->indices.size() * sizeof(unsigned int);
}

void Rectangle::set_indices(std::vector<glm::vec1> indices) {
  this->indices = indices;
}

BufferSet Rectangle::get_buffer_set() { return this->bufferSet; }
