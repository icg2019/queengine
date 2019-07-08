#ifndef RECTANGLE_HPP 
#define RECTANGLE_HPP

#include <bits/stdc++.h>
#include <glm/glm.hpp>
#include <glm/gtc/vec1.hpp>
#include "Triangle.hpp"

class Rectangle {
	private:
        Triangle upper_triangle;
        Triangle lower_triangle;

	public:
        Rectangle();
		Rectangle(
			std::vector<glm::vec3> coordinates
		);

		float* get_coordinates();
		void set_coordinates(std::vector<glm::vec3>);

        unsigned int get_coordinates_size();

		unsigned int* get_indices();
		void set_indices(std::vector<glm::vec1>);

        unsigned int get_indices_size();
};

#endif
