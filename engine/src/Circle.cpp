#include "../include/Circle.hpp"
#include "../include/point_utils.hpp"
#include <bits/stdc++.h>

class Circle {
	private:
        glm::vec3 center;
        std::vector<glm::vec3> coordinates;
        std::vector<glm::vec1> indices;
        float radius;

	public:
        Circle();
		Circle(
            glm::vec3 center,
            float radius,
            float definition
        );

		float* get_coordinates();
		void set_coordinates(std::vector<glm::vec3>);

        unsigned int get_coordinates_size();

		std::vector<glm::vec2> get_texture_coordinates();
		void set_texture_coordinates(std::vector<glm::vec2>);

		unsigned int* get_indices();
		void set_indices(std::vector<glm::vec1>);

        unsigned int get_indices_size();
};

Circle::Circle(){
    // TODO
}

Circle::Circle(glm::vec3 center, float radius, float definition) : center(center), radius(radius) {
    float intern_angle = 2 * acos(-1) / definition;

    
}
    