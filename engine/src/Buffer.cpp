#include "../include/Buffer.hpp"

Buffer::Buffer(){
    glGenBuffers(1, &this->id);
}

Buffer::~Buffer(){}
 
void Buffer::bind(GLuint program, std::string shader_var, std::vector<glm::vec3> *data){
    DEBUG("Data size" << data->size());

    glBindBuffer(GL_ARRAY_BUFFER, this->id);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * data->size(), data->data(), GL_STATIC_DRAW);

    GLint location = glGetAttribLocation(program, shader_var.c_str());

    glVertexAttribPointer(location, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void *) 0);

    glEnableVertexAttribArray(location);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Buffer::bind(GLuint program, std::string shader_var, std::vector<glm::vec2> *data){
    glBindBuffer(GL_ARRAY_BUFFER, this->id);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * data->size(), data, GL_STATIC_DRAW);

    GLint location = glGetAttribLocation(program, shader_var.c_str());
    glVertexAttribPointer(location, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void *) 0);
    glEnableVertexAttribArray(location);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Buffer::bind(GLuint program, std::string shader_var, std::vector<unsigned int> *data){
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->id);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * data->size(), data->data(), GL_STATIC_DRAW);

    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof (glm::vec1)*4, data, GL_STATIC_DRAW);
}
