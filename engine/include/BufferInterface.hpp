#ifndef BUFFER_INTERFACE_HPP
#define BUFFER_INTERFACE_HPP

class BufferInterface {

    private:
        GLuint id;

    public:
        virtual void bind(void* data) = 0;
};

#endif