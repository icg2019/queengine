#include "rectangle.hpp"

Rectangle::Rectangle(glm::vec2 a, glm::vec2 b, glm::vec2 c, glm::vec2 d){
	std::cout << "Create rectangle vertices" << std::endl;

}

Rectangle::Rectangle(glm::vec2 a, glm::vec2 b){
	std::cout << "Create rectangle 2 vertices" << std::endl;

}

Rectangle::Rectangle(double width, double height){
	std::cout << "Create rectangle lados" << std::endl;

}
