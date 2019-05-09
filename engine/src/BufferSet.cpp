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
template <class T>
void BufferSet::add(T *data) {
    glBindVertexArray(this->id);
    Buffer b = Buffer();
    b.bind(data);
    this->buffers.push_back(b);
    glBindVertexArray(0);
}
