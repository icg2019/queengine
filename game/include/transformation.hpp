#ifndef __TRANSFORMATION_HPP__
#define __TRANSFORMATION_HPP__

#include <glm/glm.hpp> 
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp> // glm::translate, glm::rotate, glm::scale
// #include <glm/gtc/matrix_clip_space.hpp> // glm::perspective
#include <glm/gtc/constants.hpp> // glm::pi

glm::mat4 camera(float Translate, glm::vec2 const& Rotate);
glm::vec4 translate(glm::vec4 const& vec);
glm::mat4 rotate(glm::mat4 translate, float rotate, glm::vec2 const& translateVector);

#endif