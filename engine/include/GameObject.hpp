#ifndef GAMEOBJECT_HPP 
#define GAMEOBJECT_HPP 

#include "BufferSet.hpp"

class GameObject {
        public:
        GameObject();
        virtual BufferSet get_buffer_set();
        virtual unsigned int get_indices_size();
};

#endif
