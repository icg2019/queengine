#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include "BufferSet.hpp"

class GameObject {
public:
  GameObject();
  virtual BufferSet get_buffer_set();
  virtual unsigned int get_indices_size();
  virtual std::vector<glm::vec3> get_coordinates();
  virtual void set_coordinates(std::vector<glm::vec3>);
  virtual int get_vertice(glm::vec3);
};

#endif
