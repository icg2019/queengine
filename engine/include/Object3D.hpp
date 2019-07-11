#ifndef OBJECT3D_HPP 
#define OBJECT3D_HPP

// #include <bits/stdc++.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <glm/glm.hpp>
#include <glm/gtc/vec1.hpp>
#include "BufferSet.hpp"
#include "GameObject.hpp"
#include "Shader.h"
#include "vboindexer.hpp"
#include "Model.hpp"

class Object3D : public GameObject {
	private:
        std::vector<glm::vec3> coordinates;
        std::vector<glm::vec2> texture_coordinates;
        std::vector<glm::vec3> normals;
        std::vector<unsigned int> indices;
        BufferSet bufferSet;


	public:
        Object3D(
            Shader shader,
            char * obj_path,
            char * mat_path,
            char * tex_path
        );

        unsigned int get_coordinates_size();

		std::vector<glm::vec2> get_texture_coordinates();
		void set_texture_coordinates(std::vector<glm::vec2>);

		std::string get_texture_path();
		void set_texture_path(const std::string&);

		std::vector<unsigned int> get_indices();
		void set_indices(std::vector<unsigned int>);

        unsigned int get_indices_size();

        bool is_a_valid_path(std::string &);

        BufferSet get_buffer_set();
        glm::vec3* get_vertice(glm::vec3);
        bool point_is_inside(glm::vec3);

};

#endif
