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

void BufferSet::add(std::vector<float> data, std::string shader_var, int type) {
    int length = data.size();

    DEBUG("Length: " << length);

    if(type == 1) {
        std::vector<glm::vec1> *vector = new std::vector<glm::vec1>();

        for(int i = 0; i < length; i++)
        {
            vector->push_back(glm::vec1(data[i]));
        }

        this->add(vector, shader_var);
    } else if (type == 2) {
        std::vector<glm::vec2> *vector = new std::vector<glm::vec2>();

        for(int i = 0; i < length; i += 2)
        {
            vector->push_back(glm::vec2({data[i], data[i+1]}));
        }

        this->add(vector, shader_var);
    } else if(type == 3) {
        std::vector<glm::vec3> *vector = new std::vector<glm::vec3>();

        for(int i = 0; i < length; i += 3)
        {
            vector->push_back(glm::vec3({data[i], data[i+1],data[i+2]}));
        }

        this->add(vector, shader_var);
    }
}

void BufferSet::add_uniform(std::vector<float> *data, std::string shader_var) {
    GLuint transformLoc = glGetUniformLocation(this->program, shader_var.c_str());
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, data->data());
}

void BufferSet::add_uniform(glm::vec3 *data, std::string shader_var) {
    GLuint transformLoc = glGetUniformLocation(this->program, shader_var.c_str());
    glUniform3f(transformLoc, data->x, data->y, data->z); 
}

void BufferSet::add_uniform(glm::vec1 *data, std::string shader_var) {
    GLuint transformLoc = glGetUniformLocation(this->program, shader_var.c_str());
    glUniform1f(transformLoc, data->x);
}
