#include "BufferSet.hpp"


BufferSet::BufferSet(GLuint program) {
    glGenVertexArrays(1, &this->id);
    this->program = program;
}

BufferSet::~BufferSet() {}

GLuint BufferSet::getId() {
    return this->id;
}

/*
    Add a new buffer to the BufferSet.
    Join multiples buffers into a VertexObjectArray
    under the hood.
*/
void BufferSet::add(glm::vec3 *data, std::string shader_var) {
    glBindVertexArray(this->id);
    Buffer b = Buffer();
    b.bind(this->program, shader_var, data);
    this->buffers.push_back(b);
    glBindVertexArray(0);
}

void BufferSet::add(glm::vec2 *data, std::string shader_var) {
    glBindVertexArray(this->id);
    Buffer b = Buffer();
    b.bind(this->program, shader_var, data);
    this->buffers.push_back(b);
    glBindVertexArray(0);
}

void BufferSet::add(glm::vec1 *data, std::string shader_var) {
    glBindVertexArray(this->id);
    Buffer b = Buffer();
    b.bind(this->program, shader_var, data);
    this->buffers.push_back(b);
    glBindVertexArray(0);
}