#include <vector>
#include <stdio.h>
#include <string>
#include <cstring>

#include <glm/glm.hpp>

#include "../include/Model.hpp"

bool load3DOBJ(
	const char * path,
	std::vector<glm::vec3> & out_vertices,
	std::vector<glm::vec2> & out_uvs,
	std::vector<glm::vec3> & out_normals
){
	printf("Loading OBJ file %s...\n", path);
  std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
	std::vector<glm::vec3> temp_vertices;      // Obj Vertices
	std::vector<glm::vec2> temp_uvs;           // Texture Coord
	std::vector<glm::vec3> temp_normals;       // Suface normals

    glm::vec3 difuse_light;
    glm::vec3 environment_light;
    glm::vec3 transformation_filter;
    unsigned int illumination;
    unsigned int optic_density;

    std::string material_file_name;            // Material

    float bigger[3] = {-999, -999, -999};
    float lower[3] = {999, 999, 999};

    FILE *file = fopen(path, "r");
    if (file == NULL) {
        printf("Impossible to open the file!\n");
        return false;
    }

    while( 1 ){
        char lineHeader[128];
        // read the first word of the line
        int res = fscanf(file, "%s", lineHeader);
        if (res == EOF) {
            break; // EOF = End Of File. Quit the loop.
        } else {
            // parse lineHeader
            if ( strcmp( lineHeader, "v" ) == 0 ){
                glm::vec3 vertex;
                fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z );

                if (vertex.x > bigger[0]) bigger[0] = vertex.x;
                if (vertex.x < lower[0])  lower[0]  = vertex.x;

                if (vertex.y > bigger[1]) bigger[1] = vertex.y;
                if (vertex.y < lower[1])  lower[1]  = vertex.y;

                if (vertex.z > bigger[2]) bigger[2] = vertex.z;
                if (vertex.z < lower[2])  lower[2]  = vertex.z;

                temp_vertices.push_back(vertex);
            } else if ( strcmp( lineHeader, "vt" ) == 0 ){
                glm::vec2 uv;
                fscanf(file, "%f %f\n", &uv.x, &uv.y );
                temp_uvs.push_back(uv);
            } else if ( strcmp( lineHeader, "vn" ) == 0 ){
                glm::vec3 normal;
                fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z );
                temp_normals.push_back(normal);
            } else if ( strcmp( lineHeader, "f" ) == 0 ){
                std::string vertex1, vertex2, vertex3;
                unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
                int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n",
                    &vertexIndex[0], &uvIndex[0], &normalIndex[0],
                    &vertexIndex[1], &uvIndex[1], &normalIndex[1],
                    &vertexIndex[2], &uvIndex[2], &normalIndex[2]
                );
                if (matches != 9){
                    printf("File can't be read by our simple parser : ( Try exporting with other options\n");
                    return false;
                }
                vertexIndices.push_back(vertexIndex[0]);
                vertexIndices.push_back(vertexIndex[1]);
                vertexIndices.push_back(vertexIndex[2]);
                uvIndices.push_back(uvIndex[0]);
                uvIndices.push_back(uvIndex[1]);
                uvIndices.push_back(uvIndex[2]);
                normalIndices.push_back(normalIndex[0]);
                normalIndices.push_back(normalIndex[1]);
                normalIndices.push_back(normalIndex[2]);
            } else if ( strcmp( lineHeader, "mtlib") == 0){
                fscanf(file, "%s", &material_file_name);
            }
        }
    }

    float temp[3] = {
        bigger[0] - lower[0],
        bigger[1] - lower[1],
        bigger[2] - lower[2]
    };

    //Normalizing ([0..1]) temp_vectors
    for( unsigned int i=0; i<temp_vertices.size(); i++){
        temp_vertices[i].x = (temp_vertices[i].x - lower[0]) / temp[0];
        temp_vertices[i].y = (temp_vertices[i].y - lower[1]) / temp[1];
        temp_vertices[i].z = (temp_vertices[i].z - lower[2]) / temp[2];
    }

    // Reading Material
    FILE *material_file = fopen(path, "r");
    if (material_file == NULL) {
        printf("Impossible to find material!\n");
    } else {
        while (1) {
            char lineHeader[128];
            int res = fscanf(material_file, "%s", lineHeader);
            if (res == EOF) {
                break;
            } else if ( strcmp(lineHeader, "illum") == 0) {
                fscanf(material_file, "%d", &illumination);
            } else if ( strcmp(lineHeader, "Kd") == 0) {
                fscanf(material_file, "%f %f %f\n",
                    &difuse_light[0], &difuse_light.y, &difuse_light.z);
            } else if ( strcmp(lineHeader, "Ka") == 0) {
                fscanf(material_file, "%f %f %f\n",
                    &environment_light.x, &environment_light.y, &environment_light.z);
            } else if ( strcmp(lineHeader, "Tf") == 0) {
                fscanf(material_file, "%f %f %f\n",
                    &transformation_filter.x, &transformation_filter.y, &transformation_filter.z);
            } else if ( strcmp(lineHeader, "Ni") == 0) {
                fscanf(material_file, "%f\n", &optic_density);
            }
        }
    }

    // For each vertex of each triangle
    for( unsigned int i=0; i<vertexIndices.size(); i++ ){
        unsigned int vertexIndex = (vertexIndices[i]);
        unsigned int uvIndex = uvIndices[i];
		unsigned int normalIndex = normalIndices[i];

        glm::vec3 vertex = temp_vertices[ vertexIndex-1 ];
		glm::vec2 uv = temp_uvs[ uvIndex-1 ];
		glm::vec3 normal = temp_normals[ normalIndex-1 ];

        out_vertices.push_back(vertex);
		out_uvs.push_back(uv);
		out_normals.push_back(normal);
    }
    fclose(file);
	return true;
}

bool loadMtl(
	Material * material,
	const char * path
){
	FILE *file = fopen(path, "r");
	if (file == NULL) {
			printf("Impossible to open the file!\n");
			return false;
	}

	// Material material;
	while(1){
		char lineHeader[128];
		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF) {
				break; // EOF = End Of File. Quit the loop.
		} else {
				// parse lineHeader
				if (strcmp(lineHeader, "Ns") == 0 ){
					fscanf(file, "%f\n", &material->obj_shininess);
				}else if (strcmp(lineHeader, "Ka") == 0 ){
					fscanf(file, "%f %f %f\n", &material->obj_ambient.x, &material->obj_ambient.y, &material->obj_ambient.z);
				}else if (strcmp(lineHeader, "Kd") == 0 ){
					fscanf(file, "%f %f %f\n", &material->obj_diffuse.x, &material->obj_diffuse.y, &material->obj_diffuse.z);
				}else if (strcmp(lineHeader, "Ks") == 0 ){
					fscanf(file, "%f %f %f\n", &material->obj_specular.x, &material->obj_specular.y, &material->obj_specular.z);
				}else if (strcmp(lineHeader, "illum") == 0 ){
					fscanf(file, "%d\n", &material->obj_illum);
				}
		}
	}
	fclose(file);
	// *material = material;

	return true;
	}
