#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>

class Texture {
public:
    Texture(std::string image_path);

    void use();

private:
    unsigned int texture_id;
};

#endif
