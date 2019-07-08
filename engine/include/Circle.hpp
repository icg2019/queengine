#ifndef CIRCLE_HPP 
#define CIRCLE_HPP

#include <bits/stdc++.h>
#include <glm/glm.hpp>
#include <glm/gtc/vec1.hpp>

class Circle {
	private:
        glm::vec3 center;
        std::vector<glm::vec3> coordinates;
        std::vector<glm::vec1> indices;
        float radius;

	public:
        Circle();
		Circle(
            glm::vec3 center,
            float radius,
            float definition
        );

		float* get_coordinates();
		void set_coordinates(std::vector<glm::vec3>);

        unsigned int get_coordinates_size();

		unsigned int* get_indices();
		void set_indices(std::vector<glm::vec1>);

        unsigned int get_indices_size();
};

#endif
