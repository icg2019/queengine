#ifndef BUFFER_SET
#define BUFFER_SET

#define ARRAY_BUFFER 0
#define TEXTURE_BUFFER 1

#include <vector>

class BufferSet {

    private:
        GLuint id;
        std::vector<GLuint> buffers;

    public:
        BufferSet();
        ~BufferSet();
        void add(int type);
};


#endif