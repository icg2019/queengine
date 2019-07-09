#ifndef __TRANSFORMATION_HPP__
#define __TRANSFORMATION_HPP__

#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/ext/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale
#include <glm/ext/matrix_clip_space.hpp> // glm::perspective
#include <glm/ext/constants.hpp> // glm::pi

glm::mat4 camera(float Translate, glm::vec2 const& Rotate);

#endif