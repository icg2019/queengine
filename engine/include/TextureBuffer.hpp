#pragma once

#define STB_IMAGE_IMPLEMENTATION

#include <glad/glad.h>
#include <stb/stb_image.h>
#include <string>

class TextureBuffer {
    private:
        bool isActive;
        GLuint id;
    public:
        TextureBuffer();
        ~TextureBuffer();
        void bind(std::string path);

        void activate();
        void deactivate();
}; 
