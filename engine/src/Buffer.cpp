#include "../include/Buffer.hpp"

Buffer::Buffer(){
    glGenBuffers(1, &this->id);
}

Buffer::~Buffer(){}

void Buffer::bind(GLuint program, std::string shader_var, glm::vec3 *data){
    glBindBuffer(GL_ARRAY_BUFFER, this->id);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3), data, GL_STATIC_DRAW);

    GLint location = glGetAttribLocation(program, shader_var.c_str());
    glVertexAttribPointer(location, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void *) 0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Buffer::bind(GLuint program, std::string shader_var, glm::vec2 *data){
    glBindBuffer(GL_ARRAY_BUFFER, this->id);
    glBufferData(GL_ARRAY_BUFFER, sizeof (glm::vec2), data, GL_STATIC_DRAW);

    GLint location = glGetAttribLocation(program, shader_var.c_str());
    glVertexAttribPointer(location, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void *) 0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Buffer::bind(GLuint program, std::string shader_var, glm::vec1 *data){
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->id);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof (glm::vec1), data, GL_STATIC_DRAW);

    GLint location = glGetAttribLocation(program, shader_var.c_str());
    glVertexAttribPointer(location, 1, GL_FLOAT, GL_FALSE, sizeof(glm::vec1), (void *) 0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
