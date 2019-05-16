#pragma once

#include <vector>

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "Buffer.hpp"
 
#include "log.h"

class BufferSet {

    private:
        GLuint id;
        GLuint program;
        std::vector<Buffer> buffers;

    public:
        BufferSet(GLuint program);
        ~BufferSet();
        
        GLuint getId();
        template <class T>
        void add(T* data, std::string shader_var){
            glBindVertexArray(this->id);

            for(Buffer b : this->buffers){
                GLint location = glGetAttribLocation(this->program, shader_var.c_str());
                //glVertexAttribPointer(location, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec3)*3, (void *) 0);
                glEnableVertexAttribArray(location);
                glBindBuffer(GL_ARRAY_BUFFER, 0);
            }

            Buffer buffer = Buffer();
            buffer.bind(this->program, shader_var, data);
            this->buffers.push_back(buffer);
            
            glBindVertexArray(0);
        }
};