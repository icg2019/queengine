#include "../include/rectangle.hpp"

Rectangle::Rectangle(glm::vec2 a, glm::vec2 b, glm::vec2 c, glm::vec2 d){
	std::cout << "Create rectangle vertices" << std::endl;
	
	std::vector<glm::vec3> coordinates = {
		glm::vec3(a[0], a[1], 0.0),
		glm::vec3(b[0], b[1], 0.0),
		glm::vec3(c[0], c[1], 0.0),
		glm::vec3(d[0], d[1], 0.0)
	};
	
	std::vector<glm::vec2> textureCoordinates = {
		glm::vec2(0.0, 0.0),
		glm::vec2(0.0, 0.0),
		glm::vec2(0.0, 0.0),
		glm::vec2(0.0, 0.0)
	};
	
	std::string texturePath = "./texture.png";
	
	std::vector<glm::vec1> indices = {
		glm::vec1(0.0),
		glm::vec1(1.0),
		glm::vec1(2.0),
		glm::vec1(0.0),
		glm::vec1(3.0),
		glm::vec1(2.0)
	};

	this->primitive = Primitive(coordinates, textureCoordinates, texturePath, indices);
}

Rectangle::Rectangle(glm::vec2 a, glm::vec2 b){
	std::cout << "Create rectangle 2 vertices" << std::endl;
	
	std::vector<glm::vec3> coordinates = {
		glm::vec3(a[0], a[1], 0.0),
		glm::vec3(b[0], a[1], 0.0),
		glm::vec3(b[0], b[1], 0.0),
		glm::vec3(a[0], b[1], 0.0)
	};
	
	std::vector<glm::vec2> textureCoordinates = {
		glm::vec2(0.0, 0.0),
		glm::vec2(0.0, 0.0),
		glm::vec2(0.0, 0.0),
		glm::vec2(0.0, 0.0)
	};

	std::string texturePath = "./texture.png";
	
	std::vector<glm::vec1> indices = {
		glm::vec1(0.0),
		glm::vec1(1.0),
		glm::vec1(2.0),
		glm::vec1(0.0),
		glm::vec1(3.0),
		glm::vec1(2.0)
	};

	this->primitive = Primitive(coordinates, textureCoordinates, texturePath, indices);
}

Rectangle::Rectangle(double width, double height){
	std::cout << "Create rectangle lados" << std::endl;
	
	std::vector<glm::vec3> coordinates = {
		glm::vec3(0.0, 0.0, 0.0),
		glm::vec3(width, 0.0, 0.0),
		glm::vec3(width, height, 0.0),
		glm::vec3(0.0, height, 0.0)
	};
	
	std::vector<glm::vec2> textureCoordinates = {
		glm::vec2(0.0, 0.0),
		glm::vec2(0.0, 0.0),
		glm::vec2(0.0, 0.0),
		glm::vec2(0.0, 0.0)
	};
	
	std::string texturePath = "./texture.png";
	
	std::vector<glm::vec1> indices = {
		glm::vec1(0.0),
		glm::vec1(1.0),
		glm::vec1(2.0),
		glm::vec1(0.0),
		glm::vec1(3.0),
		glm::vec1(2.0)
	};
	
	this->primitive = Primitive(coordinates, textureCoordinates, texturePath, indices);
}
