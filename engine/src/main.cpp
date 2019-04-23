#include <iostream>
#include <glad/glad.h>
#include <fstream>
#include <cmath>

#define INCLUDE_SDL

#include "SDL_include.h"
#include "InputManager.h"

using namespace std;

unsigned int compile_shader(string filename, bool is_fragment);

int main() {
    //Initialize SDL
    if(SDL_Init(SDL_INIT_VIDEO)) {
      cout << "SDL_Init failed: %s\n" << SDL_GetError();
      exit(-1);
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

    //criando a janela
    SDL_Window* window = SDL_CreateWindow(
      "Queengine",                  // window title
      SDL_WINDOWPOS_CENTERED,         // initial x position
      SDL_WINDOWPOS_CENTERED,         // initial y position
      0,                            // width, in pixels
      0,                            // height, in pixels
      (SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE)           // flag
    );

    SDL_MaximizeWindow(window);

    if (window == nullptr) {
      // In the case that the window could not be made...
      cout << "Fail to create Window: " << SDL_GetError() << endl;
      exit(-1);
    }

    SDL_GLContext context = SDL_GL_CreateContext(window);

    if (!gladLoadGLLoader(SDL_GL_GetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    SDL_DisplayMode currentDisplay;
    SDL_GetCurrentDisplayMode(0, &currentDisplay);
    glViewport(0, 0, currentDisplay.w, currentDisplay.h);

    float vertices[] = {
        -0.5f, 0.0f,
        0.0f, 0.75f,
        0.5f, 0.0f
    };

    unsigned int indices[] = {
        0, 1, 2
    };

    unsigned int v_shader = compile_shader("vertex.glsl", false);
    unsigned int f_shader = compile_shader("fragment.glsl", true);

    unsigned int  shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram,v_shader);
    glAttachShader(shaderProgram,f_shader);
    glLinkProgram(shaderProgram);
    glUseProgram(shaderProgram);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    unsigned int VAO;
    unsigned int  VBO, EBO;
    glGenBuffers(1,&VBO);
    glGenBuffers(1,&EBO);
    glGenVertexArrays(1, &VAO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof vertices , vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof indices, indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_TRUE, 0, (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glUseProgram(shaderProgram);
    SDL_Event event;

    while (not InputManager::GetInstance().QuitRequested()) {
        InputManager::GetInstance().Update();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
        SDL_GL_SwapWindow(window);
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    
    SDL_GL_DeleteContext(context);
    SDL_Quit();

    return 0;
}

unsigned int compile_shader(string filename, bool is_fragment) {
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