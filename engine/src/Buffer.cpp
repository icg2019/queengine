#include "../include/Buffer.hpp"

Buffer::Buffer(){
    glGenBuffers(1, &this->id);
}