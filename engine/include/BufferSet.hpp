#pragma once

#include <vector>

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "Buffer.hpp"

class BufferSet {

    private:
        GLuint id;
        GLuint program;
        std::vector<Buffer> buffers;

    public:
        BufferSet(GLuint program);
        ~BufferSet();
        
        GLuint getId();
        void add(glm::vec3* data, std::string shader_var);
        void add(glm::vec2* data, std::string shader_var);
        void add(glm::vec1* data, std::string shader_var);
};
