#include "../include/Object3D.hpp"

Object3D::Object3D(
    Shader shader,
    char * obj_path,
    char * tex_path,
    char * mat_path
    ) : bufferSet(shader.program_id) {
    
    load3DOBJ(
        obj_path,
        coordinates,
        texture_coordinates,
        normals
    );

	std::vector<glm::vec3> indexed_vertices;
	std::vector<glm::vec2> indexed_tex_coords;
	std::vector<glm::vec3> indexed_normals;
	indexVBO(
        coordinates,
        texture_coordinates,
        normals,
        indices,
        indexed_vertices,
        indexed_tex_coords,
        indexed_normals
    );

    this->bufferSet.add(&indexed_vertices, "uPosition");
  	this->bufferSet.add(&indices);
  	this->bufferSet.add(&indexed_tex_coords,"tex_coords");

    // printf("%lf\n", coordinates[0]);
}

unsigned int Object3D::get_indices_size(){
    return this->indices.size() * sizeof(unsigned int);
}

BufferSet Object3D::get_buffer_set(){
	return this->bufferSet;
}
