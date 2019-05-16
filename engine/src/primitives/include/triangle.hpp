#ifndef TRIANGLE_HPP 
#define TRIANGLE_HPP

#include "primitive.hpp"
#include <bits/stdc++.h>
#include <glm/glm.hpp>
#include <glm/gtc/vec1.hpp>

class Triangle {
	private:
		Primitive primitive;
		bool is_a_valid_triangle(double, double, double);
		bool is_a_valid_triangle(glm::vec3, glm::vec3, glm::vec3);

	public:
		Triangle();
		Triangle(glm::vec3, glm::vec3, glm::vec3);
};

#endif
