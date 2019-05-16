#include "../include/primitive.hpp"

Primitive::Primitive() :
	coordinates({glm::vec3(0)}),
	textureCoordinates({glm::vec2(0)}),
	texturePath(""),
	indices({glm::vec1(0)}) {}

Primitive::Primitive(std::vector<glm::vec3> coordinates,
		std::vector<glm::vec2> textureCoordinates,
		std::string texturePath,
		std::vector<glm::vec1> indices) :
	coordinates ( coordinates ),
	textureCoordinates ( textureCoordinates ),
	texturePath ( texturePath ),
	indices ( indices ) { }

