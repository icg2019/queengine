#include "../include/Rectangle.hpp"

Rectangle::Rectangle(){
    // Create two triangles and set the attributes to them
}

float* Rectangle::get_coordinates(){
    // Combines the coordinates of the two triangles and return them in a single array
}

void Rectangle::set_coordinates(std::vector<glm::vec3>){
    // TODO
}

unsigned int Rectangle::get_coordinates_size(){
    // Return size of the combined array
}

unsigned int* Rectangle::get_indices(){
    // Combines the two indeces arrays from the two triangles and return them as one 
}

void Rectangle::set_indices(std::vector<glm::vec1>){
    // TODO
}

unsigned int Rectangle::get_indices_size(){
    // Returns size of the combined index array
}