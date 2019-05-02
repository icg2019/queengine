#ifndef BUFFER_SET
#define BUFFER_SET

#define VERTEX_BUFFER 0
#define TEXTURE_BUFFER 1
#define ELEMENT_BUFFER 2

#include <vector>

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "Buffers.hpp"

class BufferSet {

    private:
        GLuint id;
        GLuint program;
        std::vector<BufferInterface> buffers;

    public:
        BufferSet(GLuint program);
        ~BufferSet();
        void add(int type, void* data);
};


#endif