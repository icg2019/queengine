#include "../include/Circle.hpp"
#include "../include/point_utils.hpp"
#include <bits/stdc++.h>

Circle::Circle(glm::vec3 center, float radius, float definition) : center(center), radius(radius) {
    if(definition < 3) definition = 3;

    definition = ceil(definition);

    float intern_angle = 2 * acos(-1) / definition;

    std::pair<float, float> origin = {0.0, 0.0};
    std::pair<float, float> starting_point = {radius, 0.0};
    std::pair<float, float> current_point = starting_point;

    float angle_sum = 0;

    this->coordinates.push_back({origin.first, origin.second, 0.0});

    do{
        this->coordinates.push_back({current_point.first, current_point.second, 0.0});
        current_point = rotate_point(origin, intern_angle, current_point);
        angle_sum += intern_angle;
    }while(angle_sum < 2 * acos(-1));

    for(int i = 2; i < this->coordinates.size(); i++){
        this->indices.push_back(glm::vec1(0.0));
        this->indices.push_back(glm::vec1(i-1));
        this->indices.push_back(glm::vec1(i));
    }

}

Circle::Circle(){
    this->coordinates = {
        {0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {0.707107, 0.707107, 0.0},
        {0.0, 1.0, 0.0}, {-0.707107, 0.707107, 0.0}, {-1.0, 0.0, 0.0},
        {-0.707107, -0.707107, 0.0}, {0, -1, 0}, {0.707107, -0.707107, 0},
        {1.0, 0.0, 0.0}
    };

    this->indices = {
        glm::vec1(0), glm::vec1(1), glm::vec1(2),
        glm::vec1(0), glm::vec1(2), glm::vec1(3),
        glm::vec1(0), glm::vec1(3), glm::vec1(4),
        glm::vec1(0), glm::vec1(4), glm::vec1(5),
        glm::vec1(0), glm::vec1(5), glm::vec1(6),
        glm::vec1(0), glm::vec1(6), glm::vec1(7),
        glm::vec1(0), glm::vec1(7), glm::vec1(8),
        glm::vec1(0), glm::vec1(8), glm::vec1(9),
    };
}

float* Circle::get_coordinates(){
    float* float_array = (float*) malloc(sizeof(float) * this->coordinates.size() * 3);

	for(int i = 0, array_index = 0; i < this->coordinates.size(); i++, array_index += 3){
		float_array[array_index] = this->coordinates[i].x;
		float_array[array_index+1] = this->coordinates[i].y;
		float_array[array_index+2] = this->coordinates[i].z;
	}
	
	return float_array;
}

unsigned int Circle::get_coordinates_size(){
	return this->coordinates.size() * 3 * sizeof(float);
}

void Circle::set_coordinates(std::vector<glm::vec3> coordinates){
	this->coordinates = coordinates;
}

unsigned int* Circle::get_indices(){
	unsigned int* indices_array = (unsigned int*) malloc(sizeof(unsigned int) * this->indices.size());

	for(int i = 0; i < this->indices.size(); i++){
		indices_array[i] = this->indices[i].x;
	}

	return indices_array;
}

unsigned int Circle::get_indices_size(){
	return this->indices.size() * sizeof(unsigned int);
}

void Circle::set_indices(std::vector<glm::vec1> indices){
	this->indices = indices;
}


    