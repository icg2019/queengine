#include "BufferSet.hpp"
#include <glad/glad.h>


BufferSet::BufferSet() {
    glGenVertexArrays(1, &this->id);
}

BufferSet::~BufferSet() {}

/*
    Add a new buffer to the BufferSet.
    Join multiples buffers into a VertexObjectArray
    under the hood.
*/
void BufferSet::add(int type) {
    glBindVertexArray(this->id);

    switch(type){
        case ARRAY_BUFFER:
            GLuint ARRAY;
            glGenBuffers(1, &ARRAY);
            this->buffers.push_back(ARRAY);
        break;
        case TEXTURE_BUFFER:
            GLuint TEX;
            glGenTextures(1, &TEX);
            this->buffers.push_back(TEX);
        break;
        default: break;
    }

    glBindVertexArray(0);

}