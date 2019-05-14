#include<bits/stdc++.h>
#include <glm/glm.hpp>

class Primitive {
    public:
        std::vector<glm::vec3> coordinates;
        std::vector<glm::vec2> textureCoordinates;
        std::string texturePath;
        std::vector<long long> indices;
        
		Primitive(std::vector<glm::vec3> coordinates,
            std::vector<glm::vec2> textureCoordinates,
            std::string texturePath,
            std::vector<long long> indices
        );
};
