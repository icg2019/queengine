#pragma once

#include <glm/glm.hpp>
#include <glad/glad.h>
#include <string>
#include <vector>

#include "log.h"

class Buffer {
    public:
        GLuint id;
        Buffer();
        ~Buffer();
        void bind(GLuint program, std::string shader_var, std::vector<glm::vec3> *data);
        void bind(GLuint program, std::string shader_var, std::vector<glm::vec2> *data);
        void bind(GLuint program, std::string shader_var, std::vector<unsigned int> *data);
};