#ifndef PRIMITIVE_HPP
#define PRIMITIVE_HPP

#include<bits/stdc++.h>
#include <glm/glm.hpp>
#include <glm/gtc/vec1.hpp>

class Primitive {
    public:
        std::vector<glm::vec3> coordinates;
        std::vector<glm::vec2> textureCoordinates;
        std::string texturePath;
        std::vector<glm::vec1> indices;
        
		Primitive(std::vector<glm::vec3> coordinates,
            std::vector<glm::vec2> textureCoordinates,
            std::string texturePath,
            std::vector<glm::vec1> indices
        );
        Primitive();
};

#endif
