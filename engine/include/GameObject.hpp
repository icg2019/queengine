#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include "BufferSet.hpp"
#include "Shader.h"

class GameObject {
public:
  GameObject();
  vector<Shader> shaders;
  Shader shader_used;
  virtual BufferSet get_buffer_set();
  virtual unsigned int get_indices_size();
  virtual std::vector<glm::vec3> get_coordinates();
  virtual void set_coordinates(std::vector<glm::vec3>);
  virtual int get_vertice(glm::vec3);
  virtual bool point_is_inside(glm::vec3 mouse_position);
  virtual void update_shader(std::vector<Shader> shaders);
};

#endif
