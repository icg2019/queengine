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
        
        template <class T>
        void add(T *data);
};
