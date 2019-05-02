#include "BufferInterface.hpp"

class VertexBuffer : public BufferInterface {
    public:
        VertexBuffer();
        ~VertexBuffer();
        void bind(void* data);
};


class TextureCoordBuffer : public BufferInterface {
    public:
        TextureCoordBuffer();
        ~TextureCoordBuffer();
        void bind(void* data);
};

class TextureBuffer : public BufferInterface {
    public:
        TextureBuffer();
        ~TextureBuffer();
        void bind(void* data);
};

class ElementBuffer : public BufferInterface{
    public:
        ElementBuffer();
        ~ElementBuffer();
        void bind(void* data);
}