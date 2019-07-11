#include "Shader.h"

#include <iostream>
#include <fstream>
#include <cmath>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>


using namespace std;

string BuildShaderFile(string filename) {
  ifstream file(filename);
  string line, src;

  if(file.is_open()) {
    while(getline(file, line)) src += line + "\n";
    file.close();
  } else {
    cout << "Could not load file [" << filename << "]" << endl;
    return "";
  }

  return src;
}

unsigned int CompileShader(string filename, bool is_fragment=false) {
    ifstream file(filename);
    string src = "";

    if (is_fragment){
      src += BuildShaderFile("../engine/assets/shaders/fragment_base_uniforms.glsl");
      src += BuildShaderFile(filename);
      src += BuildShaderFile("../engine/assets/shaders/fragment_main_image.glsl");
    }else{
      src += BuildShaderFile(filename);
    }

    unsigned int shader;
    if (is_fragment) shader = glCreateShader(GL_FRAGMENT_SHADER);
    else shader = glCreateShader(GL_VERTEX_SHADER);

    const char * src_str = src.c_str();
    glShaderSource(shader, 1, &src_str, NULL);
    glCompileShader(shader);

    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        char log[512];
        glGetShaderInfoLog(shader, 512, NULL, log);
        cout << "Shader [" << filename << "] compilation failed: " << log << endl;
        return 0;
    }

    return shader;
}

unsigned int CreateShaderProgram(string vertex, string fragment)
{
    int vertex_id = CompileShader(vertex);
    if (!vertex_id) return 0;

    int fragment_id = CompileShader(fragment, true);
    if (!fragment_id) return 0;

    unsigned int program;
    program = glCreateProgram();
    glAttachShader(program, vertex_id);
    glAttachShader(program, fragment_id);
    glLinkProgram(program);

    int success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success)
    {
        char log[512];
        glGetProgramInfoLog(program, 512, NULL, log);
        cout << "Program linking [" << vertex << ", " << fragment << "] failed: " << log << endl;
        return 0;
    }

    glDeleteShader(vertex_id);
    glDeleteShader(fragment_id);

    return program;

}

Shader::Shader(const string & vertex_file, const string & fragment_file)
{
    program_id = CreateShaderProgram(vertex_file, fragment_file);
}

void Shader::Use()
{
    glUseProgram(program_id);
}

unsigned int Shader::Location(const string & name) {
    unsigned int location_id = -1;

    if (locations.find(name) == locations.end())
    {
        location_id = glGetUniformLocation(program_id, name.c_str());
        if (location_id == static_cast<unsigned>(-1))
        {
            cout << "[WARN]: Shader uniform not found: " << name << endl;
        }
        else locations[name] = location_id;
    }
    else location_id = locations[name];

    return location_id;
}

void Shader::Set(const string & name, float v1)
{
    glUniform1f(Location(name), v1);
}

void Shader::Set(const string & name, float v1, float v2)
{
    glUniform2f(Location(name), v1, v2);
}

void Shader::Set(const string & name, float v1, float v2, float v3)
{
    glUniform3f(Location(name), v1, v2, v3);
}

void Shader::Set(const string & name, float v1, float v2, float v3, float v4)
{
    glUniform4f(Location(name), v1, v2, v3, v4);
}

void Shader::Set(const string & name, bool value)
{
    glUniform1i(Location(name), static_cast<int>(value));
}

void Shader::Set(const string & name, int value)
{
    glUniform1i(Location(name), value);
}

void Shader::Set(const string & name, int v1, int v2)
{
    glUniform2i(Location(name), v1, v2);
}

void Shader::Set(const string & name, int v1, int v2, int v3)
{
    glUniform3i(Location(name), v1, v2, v3);
}

void Shader::Set(const string & name, int v1, int v2, int v3, int v4)
{
    glUniform4i(Location(name), v1, v2, v3, v4);
}

void Shader::Set(const string & name, unsigned int value)
{
    glUniform1ui(Location(name), value);
}

void Shader::Set(const string & name, unsigned int v1, unsigned int v2)
{
    glUniform2ui(Location(name), v1, v2);
}

void Shader::Set(const string & name, unsigned int v1, unsigned int v2, unsigned int v3)
{
    glUniform3ui(Location(name), v1, v2, v3);
}

void Shader::Set(const string & name, unsigned int v1, unsigned int v2, unsigned int v3, unsigned int v4)
{
    glUniform4ui(Location(name), v1, v2, v3, v4);
}

void Shader::Set(const string & name, int res, float *value)
{
    // int size = value.size();
    //
    // float values[size];
    //
    // for(int i = 0; i < size; i++){
    //   values[i] = value[i];
    // }
    //
    // switch(size){
    //   case 1:
    //     glUniform1fv(Location(name), res, values);
    //     break;
    //   case 2:
    //     glUniform2fv(Location(name), res, values);
    //     break;
    //   case 3:
        glUniform3fv(Location(name), res, value);
    //     break;
    //   case 4:
    //     glUniform4fv(Location(name), res, values);
    //     break;
    // }
}

void Shader::Set(const string & name, int res, int * value)
{
    int size = sizeof(value)/sizeof(int);

    switch(size){
      case 1:
        glUniform1iv(Location(name), res, value);
        break;
      case 2:
        glUniform2iv(Location(name), res, value);
        break;
      case 3:
        glUniform3iv(Location(name), res, value);
        break;
      case 4:
        glUniform4iv(Location(name), res, value);
        break;
    }
}

void Shader::Set(const string & name, int res, unsigned int * value)
{
    int size = sizeof(value)/sizeof(unsigned int);
    switch(size){
      case 1:
        glUniform1uiv(Location(name), res, value);
        break;
      case 2:
        glUniform2uiv(Location(name), res, value);
        break;
      case 3:
        glUniform3uiv(Location(name), res, value);
        break;
      case 4:
        glUniform4uiv(Location(name), res, value);
        break;
    }
}

void Shader::Set(const string & name, const glm::mat4 & value)
{
    glUniformMatrix4fv(Location(name), 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::Set(const string & name, const glm::vec3 & value)
{
    glUniform3fv(Location(name), 1, glm::value_ptr(value));
  }


void Shader::SetTime(const string & name, function<float()> time, float frequency)
{
    Set(name, sin(frequency * time())/2.0f + 0.5f);
}
