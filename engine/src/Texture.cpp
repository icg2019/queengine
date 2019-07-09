#include "Texture.h"

#include <glad/glad.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>
#include <iostream>

using namespace std;

Texture::Texture(std::string image_path)
{
    glGenTextures(1, &texture_id);
    glBindTexture(GL_TEXTURE_2D, texture_id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_set_flip_vertically_on_load(true);

    int width, height, nrChannels;
    unsigned char * data = stbi_load(image_path.c_str(), &width, &height,
                                     &nrChannels, 0);

    if (data)
    {
        cout << "Loaded image " << image_path << " :: (" << width << ", " << height << ") :: nrChannels = " << nrChannels;

        auto inner_format = GL_RGB;
        if (nrChannels == 4) inner_format = GL_RGBA;

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0,
                     inner_format, GL_UNSIGNED_BYTE, data);

        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        printf("Failed to load texture");
    }

    // glBindTexture(GL_TEXTURE_2D, 0);
    stbi_image_free(data);
}

void Texture::use()
{
    glBindTexture(GL_TEXTURE_2D, texture_id);
}

