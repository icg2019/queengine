#include "../include/triangle.hpp"

Triangle::Triangle(){
	std::clog << "Create triangle with success\n";

	std::vector<glm::vec3> coordinates = {
		glm::vec3(0.0, 0.0, 0.0),
		glm::vec3(1.0, 1.0, 1.0),
		glm::vec3(0.5, 0.5, 0.5),
	};

	std::vector<glm::vec2> textureCoordinates = {
		glm::vec2(0.0, 0.0),
		glm::vec2(1.0, 1.0),
		glm::vec2(0.5, 0.5),
	};

	// Criar metodo para Verificar se o caminho da textura esta certo
	std::string texturePath = "./texture.png";

	// Verificar o que é
	std::vector<glm::vec1> indices = {
		glm::vec1(0.0),
		glm::vec1(1.0),
		glm::vec1(2.0),
		glm::vec1(3.0),
		glm::vec1(0.0)
	};

	this->primitive = Primitive(coordinates, textureCoordinates, texturePath, indices);
}

Triangle::Triangle(glm::vec3 a, glm::vec3 b, glm::vec3 c){
	std::clog << "Create triangle with points success\n";
	std::vector<glm::vec3> coordinates = {
		glm::vec3(a[0], a[1], a[2]),
		glm::vec3(b[0], b[1], b[2]),
		glm::vec3(c[0], c[1], c[2]),
	};

	std::vector<glm::vec2> textureCoordinates = {
		glm::vec2(a[0], a[1]),
		glm::vec2(b[0], b[1]),
		glm::vec2(c[0], c[1]),
	};

	std::string texturePath = "./texture.png";

	std::vector<glm::vec1> indices = {
		glm::vec1(0.0),
		glm::vec1(1.0),
		glm::vec1(2.0),
		glm::vec1(3.0),
		glm::vec1(0.0)
	};

	this->primitive = Primitive(coordinates, textureCoordinates, texturePath, indices);
}


// TODO Create validation for points
bool Triangle::is_a_valid_triangle(double a, double b, double c){
	return (a <= b+c && b <= c+a && c <= a+b);
}

bool Triangle::is_a_valid_triangle(glm::vec3 a, glm::vec3 b, glm::vec3 c){
	double det = abs((a[0]*b[1] + a[1]*c[0] + b[0]*c[1]) - (c[0]*b[1] + c[1]*a[0] + b[0]*a[1]));
	return det != 0;
}
