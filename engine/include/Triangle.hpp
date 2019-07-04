#ifndef TRIANGLE_HPP 
#define TRIANGLE_HPP

#include <bits/stdc++.h>
#include <glm/glm.hpp>
#include <glm/gtc/vec1.hpp>

class Triangle {
	private:
        std::vector<glm::vec3> coordinates;
        std::vector<glm::vec2> texture_coordinates;
        std::string texture_path;
        std::vector<glm::vec1> indices;

	public:
        Triangle();
		Triangle(
            std::vector<glm::vec3> coordinates,
            std::vector<glm::vec2> textureCoordinates,
            std::string texturePath,
            std::vector<glm::vec1> indices
        );

		float* get_coordinates();
		void set_coordinates(std::vector<glm::vec3>);

		std::vector<glm::vec2> get_texture_coordinates();
		void set_texture_coordinates(std::vector<glm::vec2>);

		std::string get_texture_path();
		void set_texture_path(const std::string&);

		unsigned int* get_indices();
		void set_indices(std::vector<glm::vec1>);

        bool is_a_valid_path(std::string &);

        // Calcular a normal da face do triangulo
};

#endif
