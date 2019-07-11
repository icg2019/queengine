#ifndef OBJLOADER_H
#define OBJLOADER_H

// Read an .obj file and load the vertices, uvs and normals
// return true if the obj was loaded with success
bool load3DOBJ(
	const char * path, 
	std::vector<glm::vec3> & out_vertices, 
	std::vector<glm::vec2> & out_uvs, 
	std::vector<glm::vec3> & out_normals
);

#endif