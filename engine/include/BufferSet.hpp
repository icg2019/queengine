#pragma once

#include <vector>

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "Buffer.hpp"
 
#include "log.h"

class BufferSet {

    private:
        GLuint id;

    public:
        GLuint program;
        std::vector<Buffer> buffers;
        BufferSet(GLuint program);
        ~BufferSet();
        
        GLuint getId();
        template <class T>
        void add(std::vector<T> *data, std::string shader_var = ""){
            glBindVertexArray(this->id);

            for(Buffer b : this->buffers){
                GLint location = glGetAttribLocation(this->program, b.shader_var.c_str());
                glEnableVertexAttribArray(location);
                glBindBuffer(GL_ARRAY_BUFFER, 0);
            }

            Buffer buffer = Buffer();
            buffer.bind(this->program, shader_var, data);
            this->buffers.push_back(buffer);
            
            glBindVertexArray(0);
        }

        template <class T>
        void resize(std::vector<T> *data, std::string shader_var = "")
        {
            INFO("BufferSet Resize");

            glBindVertexArray(this->id);

            for(Buffer b : this->buffers)
            {
                if(b.shader_var.c_str() != shader_var)
                {
                    GLint location = glGetAttribLocation(this->program, shader_var.c_str());
                    glEnableVertexAttribArray(location);
                    glBindBuffer(GL_ARRAY_BUFFER, 0);
                }
                else
                {
                    // INFO("Sizeof (T): " << sizeof(T));
                    // INFO("data->size(): " << data->size());
                    // INFO("Buffer id: " << b.id);
                    // INFO("data->data()[0]" << data->data());
                    b.bind(this->program, shader_var, data);
                }
            }

            glBindVertexArray(0);
        }

        void add(std::vector<float> , std::string, int);

        void add_uniform(std::vector<float> *data, std::string shader_var);
        
        void add_uniform(glm::vec3 *data, std::string shader_var);

        void add_uniform(glm::vec1 *data, std::string shader_var);
};