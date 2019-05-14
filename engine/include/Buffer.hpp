#pragma once

#include <glm/glm.hpp>
#include <glad/glad.h>
#include <string>

class Buffer {
    public:
        GLuint id;
        Buffer();
        ~Buffer();
        void bind(GLuint program, std::string shader_var, glm::vec3 *data);
        void bind(GLuint program, std::string shader_var, glm::vec2 *data);
        void bind(GLuint program, std::string shader_var, glm::vec1 *data);
};