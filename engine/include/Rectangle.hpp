#ifndef RECTANGLE_HPP 
#define RECTANGLE_HPP

// #include <bits/stdc++.h>
#include <string>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/vec1.hpp>
#include "Triangle.hpp"
#include "Shader.h"

class Rectangle {
	private:
        Triangle upper_triangle;
        Triangle lower_triangle;

	public:
        Rectangle(Shader shader);
		Rectangle(
			Shader shader,
			std::vector<glm::vec3> coordinates
		);

		std::vector<float> get_coordinates();
		void set_coordinates(std::vector<glm::vec3>);

        unsigned int get_coordinates_size();

		std::vector<unsigned int> get_indices();
		void set_indices(std::vector<glm::vec1>);

        unsigned int get_indices_size();
};

#endif
