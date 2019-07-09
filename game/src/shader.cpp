#include "shader.hpp"

#include <iostream>
#include <fstream>
#include <cmath>

#include <glad/glad.h>



using namespace std;

unsigned int compile_shader(string filename, bool is_fragment=false)
{
    ifstream file(filename);
    string src = "";

    if(file.is_open())
    {
        string line;
        while(getline(file, line)) src += line + "\n";
        file.close();
    }
    else
    {
        cout << "Could not load file [" << filename << "]" << endl;
        return 0;
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

unsigned int create_shader_program(string vertex, string fragment)
{
    int vertex_id = compile_shader(vertex);
    if (!vertex_id) return 0;

    int fragment_id = compile_shader(fragment, true);
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

Shader::Shader(const std::string & vertex_file, const std::string & fragment_file)
{
    program_id = create_shader_program(vertex_file, fragment_file);
}

void Shader::use()
{
    glUseProgram(program_id);
}

unsigned int Shader::location(const std::string & name) {
    unsigned int location_id = -1;

    if (locations.find(name) == locations.end())
    {
        location_id = glGetUniformLocation(program_id, name.c_str());
  
    }
    else location_id = locations[name];

    return location_id;
}

void Shader::set(const std::string & name, bool value)
{
    glUniform1i(location(name), static_cast<int>(value));
}

void Shader::set(const std::string & name, int value)
{
    glUniform1i(location(name), value);
}

void Shader::set(const std::string & name, unsigned int value)
{
    glUniform1ui(location(name), value);
}

void Shader::set(const std::string & name, float v1)
{
    glUniform1f(location(name), v1);
}

void Shader::set(const std::string & name, float v1, float v2)
{
    glUniform2f(location(name), v1, v2);
}

void Shader::set(const std::string & name, float v1, float v2, float v3)
{
    glUniform3f(location(name), v1, v2, v3);
}

void Shader::set(const std::string & name, float v1, float v2, float v3, float v4)
{
    glUniform4f(location(name), v1, v2, v3, v4);
}


