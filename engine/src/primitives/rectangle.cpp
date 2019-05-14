#include "rectangle.hpp"
#include <gl/glm.hpp>

Rectangle::Rectangle(glm::vec2 a, glm::vec2 b, glm::vec2 c, glm::vec2 d){
	cout << "Create rectangle vertices" << endl;

}

Rectangle::Rectangle(glm::vec2 a, glm::vec2 b){
	cout << "Create rectangle 2 vertices" << endl;

}

Rectangle::Rectangle(double width, double height){
	cout << "Create rectangle lados" << endl;

}
