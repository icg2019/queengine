#include "BufferSet.hpp"
 

BufferSet::BufferSet(GLuint program) {
    INFO("VAO ID " << this->id);
    glGenVertexArrays(1, &this->id);
    this->program = program;
    INFO("After VAO ID " << this->id);
}

BufferSet::~BufferSet() {}

GLuint BufferSet::getId() {
    return this->id;
}