#include <iostream>
#include <glad/glad.h>
#include <fstream>
#include <cmath>
#include <vector>
#include <glm/glm.hpp>

#define INCLUDE_SDL
#include <glm/gtc/matrix_transform.hpp>

#include "SDL_include.h"
#include "InputManager.h"
#include "Queengine.h"
#include "texture.hpp"
#include "Model.hpp"
#include "vboindexer.hpp"


using namespace std;

unsigned int CompileShader(string filename, bool is_fragment);

int main(int argc, char **argv) {
  Queengine *engine = Queengine::GetInstance();

	// Projection matrix : 45� Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	glm::mat4 Projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);
	// Or, for an ortho camera :
	//glm::mat4 Projection = glm::ortho(-10.0f,10.0f,-10.0f,10.0f,0.0f,100.0f); // In world coordinates
	
	// Camera matrix
	glm::mat4 View = glm::lookAt(
								glm::vec3(4,3,-3), // Camera is at (4,3,-3), in World Space
								glm::vec3(0,0,0), // and looks at the origin
								glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
						   );
	// Model matrix : an identity matrix (model will be at the origin)
	glm::mat4 Model      = glm::mat4(1.0f);
	// Our ModelViewProjection : multiplication of our 3 matrices
	glm::mat4 MVP        = Projection * View * Model; // Remember, matrix multiplication is the other way around
  // This part needs to be extracted later to a scene or whatever
  // -------------------------------------------------------------------------------------------------- //
 
  std::vector<glm::vec3> vertices;
  std::vector<glm::vec2> textcoord;
  std::vector<glm::vec3> normal;

  bool fileOpened = load3DOBJ("engine/assets/obj/cube.obj", vertices, textcoord, normal);

  unsigned int indices[vertices.size()];

  for(int i = 0; i < vertices.size();i++) {
    indices[i] = i;
  }

  unsigned int v_shader = CompileShader("vertex.glsl", false);
  unsigned int f_shader = CompileShader("fragment.glsl", true);

  unsigned int  shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram,v_shader);
  glAttachShader(shaderProgram,f_shader);
  glLinkProgram(shaderProgram);
  glUseProgram(shaderProgram);

   // Load the texture using any two methods
	GLuint Texture = loadBMP_custom("engine/assets/uvtemplate.bmp");
	
	// Get a handle for our "myTextureSampler" uniform
	GLuint TextureID  = glGetUniformLocation(shaderProgram, "myTextureSampler");

// Get a handle for our "MVP" uniform
	GLuint MatrixID = glGetUniformLocation(shaderProgram, "MVP");
  GLuint ViewMatrixID = glGetUniformLocation(shaderProgram, "V");
	GLuint ModelMatrixID = glGetUniformLocation(shaderProgram, "M");
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

  // Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);

  // Send our transformation to the currently bound shader, 
		// in the "MVP" uniform
  glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
		glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &Model[0][0]);
		glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, &View[0][0]);

  // Bind our texture in Texture Unit 0
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, Texture);
  // Set our "myTextureSampler" sampler to use Texture Unit 0
  glUniform1i(TextureID, 0);
  

  unsigned int VAO;
  unsigned int  VBO, EBO, NBO;
  GLuint uvbuffer;
  glGenBuffers(1,&VBO);
  glGenBuffers(1,&EBO);
  glGenBuffers(1,&NBO);
	glGenBuffers(1, &uvbuffer);

  glGenVertexArrays(1, &VAO);

  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);
  
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof indices, indices, GL_STATIC_DRAW);


  // 1st attribute buffer : vertices
  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glVertexAttribPointer(
    0,
    3,
    GL_FLOAT,
    GL_TRUE,
    0,
    (void*)0
  );

  // 3rd attribute buffer : uvs
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, textcoord.size() * sizeof(glm::vec2), &textcoord[0], GL_STATIC_DRAW);
  
  glEnableVertexAttribArray(1);
  glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
  glVertexAttribPointer(
    1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
    2,                                // size
    GL_FLOAT,                         // type
    GL_FALSE,                         // normalized?
    0,                                // stride
    (void*)0                          // array buffer offset
  );
  glEnableVertexAttribArray(0);

    // 2nd attribute buffer : normals
  glBindBuffer(GL_ARRAY_BUFFER, NBO);
  glBufferData(GL_ARRAY_BUFFER, normal.size() * sizeof(glm::vec3), &normal[0], GL_STATIC_DRAW);

  glEnableVertexAttribArray(2);
  glVertexAttribPointer(
    2,                                // attribute. No particular reason for 1, but must match the layout in the shader.
    3,                                // size
    GL_FLOAT,                         // type
    GL_FALSE,                         // normalized?
    0,                                // stride
    (void*)0                          // array buffer offset
  );

  glUseProgram(shaderProgram);
	GLuint LightID = glGetUniformLocation(shaderProgram, "LightPosition_worldspace");

  glm::vec3 lightPos = glm::vec3(4,4,4);
  glUniform3f(LightID, lightPos.x, lightPos.y, lightPos.z);

  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

  glUseProgram(shaderProgram);
  // -------------------------------------------------------------------------------------------------- //

  engine->Run(VAO, vertices.size());

  return 0;
}

unsigned int CompileShader(string filename, bool is_fragment) {
  filename = "engine/assets/shaders/" + filename;
  ifstream file(filename);
  string src = "";

  if(file.is_open()) {
    string line;
    while(getline(file, line)) src += line + "\n";
    file.close();
  } else {
    cout << "Could not load file [" << filename << "]" << endl;
    return 0;
  }

  unsigned int shader;
  if (is_fragment) {
    shader = glCreateShader(GL_FRAGMENT_SHADER);
  } else {
    shader = glCreateShader(GL_VERTEX_SHADER);
  }

  const char * src_str = src.c_str();
  glShaderSource(shader, 1, &src_str, NULL);
  glCompileShader(shader);

  int success;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    char log[512];
    glGetShaderInfoLog(shader, 512, NULL, log);
    cout << "Shader [" << filename << "] compilation failed: " << log << endl;
    return 0;
  }

  return shader;
}