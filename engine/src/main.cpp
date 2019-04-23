#include <iostream>
#include <glad/glad.h>
#include <fstream>
#include <cmath>

#define INCLUDE_SDL

#include "SDL_include.h"

using namespace std;

int main()
{
    //Initialize SDL
    if(SDL_Init(SDL_INIT_VIDEO)){
      cout << "SDL_Init failed: %s\n" << SDL_GetError();
      exit(-1);
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

    //criando a janela
    //TODO Make the window fullscreen

    SDL_Window* window = SDL_CreateWindow(
      "Queengine",                  // window title
      SDL_WINDOWPOS_CENTERED,         // initial x position
      SDL_WINDOWPOS_CENTERED,         // initial y position
      1000,                            // width, in pixels
      800,                            // height, in pixels
      SDL_WINDOW_OPENGL           // flag
    );

    if (window == nullptr) {
      // In the case that the window could not be made...
      cout << "Fail to create Window: " << SDL_GetError() << endl;
      exit(-1);
    }

    SDL_GLContext context = SDL_GL_CreateContext(window); 
   
    

    if (!gladLoadGLLoader(SDL_GL_GetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    int screenWidth = 800;
    int screenHeight = 600;
    glViewport(0, 0, screenWidth, screenHeight);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    float vertices[] = {
        //   x      y     z        r     g     b        s     t
        0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.5f, 1.0f};

    unsigned int indices[] = {
        0, 1, 2};

    unsigned int VBO;
    glGenBuffers(1, &VBO);

    unsigned int EBO;
    glGenBuffers(1, &EBO);

    unsigned int VAO;
    glGenVertexArrays(1, &VAO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof vertices, vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof indices, indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glEnable(GL_DEPTH_TEST);

    while (true)
    {
        // processInput(window);

        //TODO Add the input manager

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glBindVertexArray(0);

        SDL_GL_SwapWindow(window);
    }


    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    
    SDL_GL_DeleteContext(context);
    SDL_Quit();

    return 0;
}
