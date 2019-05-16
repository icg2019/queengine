#include "../include/primitive.hpp"

Primitive::Primitive(std::vector<glm::vec3> coordinates,
		std::vector<glm::vec2> textureCoordinates,
		std::string texturePath,
		std::vector<glm::vec1> indices){

	this->coordinates = coordinates;
	this->textureCoordinates = textureCoordinates;
	this->texturePath = texturePath;
	this->indices = indices;
}

Primitive::Primitive(){

}
