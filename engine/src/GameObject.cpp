#include "../include/GameObject.hpp"

GameObject::GameObject() {}
BufferSet GameObject::get_buffer_set() {}
unsigned int GameObject::get_indices_size() {}
std::vector<glm::vec3> GameObject::get_coordinates() {}
void GameObject::set_coordinates(std::vector<glm::vec3>) {}
int GameObject::get_vertice(glm::vec3 mouse_position) {}
bool GameObject::point_is_inside(glm::vec3 mouse_position) {}
void GameObject::update_shader(std::vector<Shader> shaders) {}
