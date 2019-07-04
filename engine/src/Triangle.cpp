#include "../include/Triangle.hpp"

Triangle::Triangle() {
	std::vector<glm::vec3> coordinates = {
		glm::vec3(-0.5, 0.0, 0.0),
		glm::vec3(0.0, 0.75, 0.0),
		glm::vec3(0.5, 0.0, 0.0),
	};

	std::vector<glm::vec2> texture_coordinates = {
		glm::vec2(0.0, 0.0),
		glm::vec2(1.0, 1.0),
		glm::vec2(0.5, 0.5),
	};

	// Criar metodo para Verificar se o caminho da textura esta certo
	std::string texture_path = "./texture.png";

	// Verificar o que é
	std::vector<glm::vec1> indices = {
		glm::vec1(0.0),
		glm::vec1(1.0),
		glm::vec1(2.0),
	};

    this->coordinates = coordinates;
	this->texture_coordinates = texture_coordinates;
    this->texture_path = texture_path;
    this->indices = indices;

	std::clog << "Create triangle with success\n";
}

Triangle::Triangle(std::vector<glm::vec3> coordinates,
		std::vector<glm::vec2> texture_coordinates,
		std::string texture_path,
		std::vector<glm::vec1> indices) :
	coordinates( coordinates ),
	texture_coordinates( texture_coordinates ),
	texture_path( texture_path ),
	indices ( indices ) {
        std::cout << "Create triangle with constructor" << std::endl;
}

float* Triangle::get_coordinates(){
	float* float_array = (float*) malloc(sizeof(float) * this->coordinates.size() * 2);

	for(int i = 0, array_index = 0; i < this->coordinates.size(); i++, array_index += 2){
		float_array[array_index] = this->coordinates[i].x;
		float_array[array_index+1] = this->coordinates[i].y;
	}
	
	return float_array;
}

unsigned int Triangle::get_coordinates_size(){
	return this->coordinates.size() * 2 * sizeof(float);
}

void Triangle::set_coordinates(std::vector<glm::vec3> coordinates){
	this->coordinates = coordinates;
}

std::vector<glm::vec2> Triangle::get_texture_coordinates(){
	return this->texture_coordinates;
}

void Triangle::set_texture_coordinates(std::vector<glm::vec2> texture_coordinates){
	this->texture_coordinates = texture_coordinates;
}

std::string Triangle::get_texture_path(){
	return this->texture_path;
}

void Triangle::set_texture_path(const std::string &texture_path){
	this->texture_path = texture_path;
}

unsigned int* Triangle::get_indices(){
	unsigned int* indices_array = (unsigned int*) malloc(sizeof(unsigned int) * this->indices.size());

	for(int i = 0; i < this->indices.size(); i++){
		indices_array[i] = this->indices[i].x;
	}

	return indices_array;
}

unsigned int Triangle::get_indices_size(){
	return this->indices.size() * sizeof(unsigned int);
}

void Triangle::set_indices(std::vector<glm::vec1> indices){
	this->indices = indices;
}

bool Triangle::is_a_valid_path(std::string &path){
 std::ifstream path_checked(path);
  if (!path_checked)
  {
      std::cout << "The file doesn't exist" << std::endl;
      return false;
  }
  return true;
}
