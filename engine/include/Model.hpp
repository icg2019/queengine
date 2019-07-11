#ifndef OBJLOADER_H
#define OBJLOADER_H

// Read an .obj file and load the vertices, uvs and normals
// return true if the obj was loaded with success

struct Material{
	glm::vec3 obj_diffuse;
	glm::vec3 obj_ambient;
	glm::vec3 obj_specular;
	float obj_shininess;
	int obj_illum;
}typedef Material;

bool load3DOBJ(
	const char * path,
	std::vector<glm::vec3> & out_vertices,
	std::vector<glm::vec2> & out_uvs,
	std::vector<glm::vec3> & out_normals
);

bool loadMtl(
	Material *material,
	const char * path
);

#endif
