#ifndef CIRCLE_HPP 
#define CIRCLE_HPP

// #include <bits/stdc++.h>
#include <vector>
#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/vec1.hpp>

#include "Shader.h"
#include "BufferSet.hpp"
#include "GameObject.hpp"

class Circle : public GameObject {
	private:
        glm::vec3 center;
        std::vector<glm::vec3> coordinates;
        std::vector<glm::vec1> indices;
        float radius;
        BufferSet bufferSet;

	public:
        Circle(Shader shader);
		Circle(
            Shader shader,
            glm::vec3 center,
            float radius,
            float definition
        );

		std::vector<glm::vec3> get_coordinates();
		void set_coordinates(std::vector<glm::vec3>);

        unsigned int get_coordinates_size();

		std::vector<unsigned int> get_indices();
		void set_indices(std::vector<glm::vec1>);

        unsigned int get_indices_size();

        std::vector<glm::vec2> get_texture_coordinates();

        BufferSet get_buffer_set();
};

#endif
