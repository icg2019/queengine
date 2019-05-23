#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "primitive.hpp"
#include <bits/stdc++.h>
#include <glm/glm.hpp>
#include <glm/gtc/vec1.hpp>

class Rectangle {
	private:
		Primitive primitive;

	public:
		Rectangle(glm::vec2, glm::vec2, glm::vec2, glm::vec2);
		Rectangle(glm::vec2, glm::vec2);
		Rectangle(double, double);
};

#endif
