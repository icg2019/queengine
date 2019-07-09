#include "BufferSet.hpp"


BufferSet::BufferSet(GLuint program) {
    glGenVertexArrays(1, &this->id);
    this->program = program;
}

BufferSet::~BufferSet() {}

/*
    Add a new buffer to the BufferSet.
    Join multiples buffers into a VertexObjectArray
    under the hood.
*/
void BufferSet::add(int type, void* data) {
    glBindVertexArray(this->id);

    switch(type){
        case VERTEX_BUFFER:
            BufferInterface b = VertexBuffer();
            b.bind(data);
            break;
        case ELEMENT_BUFFER:
            BufferInterface b = ElementBuffer();
            b.bind(data);
            break;
        case TEXTURE_BUFFER:
            BufferInterface b = TextureBuffer();            
            b.bind(data);
            break;
        default: break;
    }

    glBindVertexArray(0);

}