#include <string>
#include "BufferSet.hpp"

/*
    Add a new buffer to the BufferSet.
    Join multiples buffers into a VertexObjectArray
    under the hood.
*/
template <class T>
void BufferSet::add(T *data, std::string shader_var) {
    glBindVertexArray(this->id);
    Buffer b = Buffer();
    b.bind(this->program, shader_var, data);
    this->buffers.push_back(b);
    glBindVertexArray(0);
}