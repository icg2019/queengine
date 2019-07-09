// #include "../include/TextureBuffer.hpp"


// TextureBuffer::TextureBuffer() {
//     glGenTextures(1, &this->id); 
//     this->isActive = true;
// }

// void TextureBuffer::bind(std::string path) {
//     int width, height, nrChannels;

//     // Carrega textura
//     unsigned char *data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);    

//     if(data) {
//         glBindTexture(GL_TEXTURE_2D, this->id);
//         glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
//         glGenerateMipmap(GL_TEXTURE_2D);
//     }
//     stbi_image_free(data);
//     glBindTexture(this->id, 0);
// }
 
// void TextureBuffer::activate() {
//     this->isActive = true;
// }

// void TextureBuffer::deactivate() {
//     this->isActive = false;
// }