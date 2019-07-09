#include "../include/Rectangle.hpp"
#include "../include/Triangle.hpp"
#include <set>

Rectangle::Rectangle(){
    // Create two triangles and set the attributes to them
}

Rectangle::Rectangle(std::vector<glm::vec3> coordinates){
    if(coordinates.size() != 4){
        throw "Rectangle must contain 4 coordinates";
    }

    std::vector<glm::vec3> coordinates_upper_triangle = {};
    std::vector<glm::vec1> indices_upper_triangle = {};

    std::vector<glm::vec3> coordinates_lower_triangle = {};
    std::vector<glm::vec1> indices_lower_triangle = {};

    for(int i = 0; i < coordinates.size(); i++){
        if(i < 3) { // coordinates for upper triangle
            coordinates_upper_triangle.push_back(coordinates[i]);
        }
        if(i > 0) { // coordinates for lower triangle
            coordinates_lower_triangle.push_back(coordinates[i]);
        }
	}

    for(int i = 0; i < 3; i++){
        indices_upper_triangle.push_back(glm::vec1(i));
        indices_lower_triangle.push_back(glm::vec1(i+3));
    }

    this->upper_triangle = Triangle(coordinates_upper_triangle, indices_upper_triangle);
    this->lower_triangle = Triangle(coordinates_lower_triangle, indices_lower_triangle);
}

std::vector<glm::vec3> Rectangle::get_coordinates(){
    std::vector<glm::vec3> rec(this->upper_triangle.get_coordinates().begin(), this->upper_triangle.get_coordinates().end());
    rec.push_back(this->lower_triangle.get_coordinates()[2]);

    return rec;
}

void Rectangle::set_coordinates(std::vector<glm::vec3>){
    // TODO
}

unsigned int Rectangle::get_coordinates_size(){
    // Return size of the combined array
    return this->upper_triangle.get_coordinates_size() + this->lower_triangle.get_coordinates_size();
}

std::vector<unsigned int> Rectangle::get_indices(){
    // Combines the two indeces arrays from the two triangles and return them as one
    int number_of_indices = 6; // Each point of both triangles has an indice
    std::vector<unsigned int> indices_array = std::vector<unsigned int>(number_of_indices);
    std::vector<unsigned int> indices_upper_triangle = this->upper_triangle.get_indices();
    std::vector<unsigned int> indices_lower_triangle = this->lower_triangle.get_indices();

    // memcpy(indices_array, indices_upper_triangle, sizeof(unsigned int) * 3);
    // memcpy(indices_array + (sizeof(unsigned int) * 3), indices_lower_triangle, sizeof(unsigned int) * 3);

    for(size_t i = 0; i < 3; i++){
        indices_array[i] = indices_upper_triangle[i];
        indices_array[i+3] = indices_lower_triangle[i];
    }

    return indices_array;
}

void Rectangle::set_indices(std::vector<glm::vec1>){
    // TODO
}

unsigned int Rectangle::get_indices_size(){
    // Returns size of the combined index array
    return this->upper_triangle.get_indices_size() + this->lower_triangle.get_indices_size();
}