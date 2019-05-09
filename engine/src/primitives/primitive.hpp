#include<bits/stdc++.h>
#include<gl/glm.hpp>

class Primitive {
    public:
        std::vector<glm::vec3> coordinates;
        std::vector<glm::vec2> textureCoordinates;
        std::string texturePath;
        std::vector<glm::vec1> indices;
        
        Primitive::Primitive(std::vector<glm::vec3> coordinates,
            std::vector<glm::vec2> textureCoordinates,
            std::string texturePath,
            std::vector<glm::vec1> indices
        );
}
