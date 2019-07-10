#ifndef GAMEOBJECT_HPP 
#define GAMEOBJECT_HPP 

#include "BufferSet.hpp"

class GameObject {
	public:
        GameObject();
        BufferSet get_buffer_set();
        unsigned int get_indices_size();
};

#endif
