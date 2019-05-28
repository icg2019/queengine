#pragma once

#include <glm/glm.hpp>
#include <glad/glad.h>

#include <string>
#include <vector>
#include <typeinfo>

#include "log.h"

class Buffer {
    public:
        GLuint id;
        Buffer();

        template <class T>
        void bind(GLuint program, std::string shader_var, std::vector<T> *data)
        {
            if(typeid(T) != typeid(unsigned int)) {
                glBindBuffer(GL_ARRAY_BUFFER, this->id);
                glBufferData(GL_ARRAY_BUFFER, sizeof(T) * data->size(), data->data(), GL_STATIC_DRAW);

                GLint location = glGetAttribLocation(program, shader_var.c_str());
                glVertexAttribPointer(location, 3, GL_FLOAT, GL_FALSE, sizeof(T), (void *) 0);
                glEnableVertexAttribArray(location);
            }
            else {
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->id);
                glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(T) * data->size(), data->data(), GL_STATIC_DRAW);
            }

            glBindBuffer(GL_ARRAY_BUFFER, 0);
        }

};