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

		std::vector<glm::vec3> getCoordinates();
		void setCoordinates(std::vector<glm::vec3>);

		std::vector<glm::vec2> getTextureCoordinates();
		void getTextureCoordinates(std::vector<glm::vec2>);

		std::string getTexturePath();
		void setTexturePath(std::string);

		std::vector<glm::vec1> getIndices();
		void setIndices(std::vector<glm::vec1>);

};

#endif
