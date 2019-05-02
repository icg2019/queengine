#include "Buffers.hpp"

GLuint createArrayBuffer(){
    GLuint* ARRAY;
    glGenBuffers(1, ARRAY);
    return ARRAY;
}

VertexBuffer::VertexBuffer(){
    this->id = createArrayBuffer();
}

ElementBuffer::ElementBuffer(){
    this->id = createArrayBuffer();
}

TextureCoordBuffer::TextureCoordBuffer(){
    this->id = createArrayBuffer();
}

TextureBuffer::TextureBuffer(){
    GLuint TEX;
    glGenTextures(1, &TEX);
    this->id = TEX;    
}

void VertexBuffer::bind(void* data){
    glBindBuffer(GL_ARRAY_BUFFER, this->id);
    glBufferData(GL_ARRAY_BUFFER, sizeof glm::vec3, data, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, glm::vec3, (void *) 0);
}

void ElementBuffer::Bind(void* data){
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->id);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof data, data, glDrawUsage);
}

void TextureCoordBuffer::bind(void* data){

}

void TextureBuffer::bind(void* data){

}