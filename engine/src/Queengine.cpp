#include "Queengine.h"
#include <iostream>
#include <glad/glad.h>
#include <fstream>
#include <cmath>
#include <unistd.h>
#include <vector>

#include "InputManager.h"

Queengine *Queengine::instance = nullptr;

Queengine::Queengine() {
    if(SDL_Init(SDL_INIT_VIDEO)) {
      std::cout << "SDL_Init failed: %s\n" << SDL_GetError();
      exit(-1);
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

    this->window = SDL_CreateWindow(
      "Queengine",
      SDL_WINDOWPOS_CENTERED,
      SDL_WINDOWPOS_CENTERED,
      0,
      0,
      (SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE)
    );

    SDL_MaximizeWindow(this->window);

    if (this->window == nullptr) {
      std::cout << "Fail to create Window: " << SDL_GetError() << std::endl;
      exit(-1);
    }

    this->context = SDL_GL_CreateContext(this->window);

    if (!gladLoadGLLoader(SDL_GL_GetProcAddress)) {
      std::cout << "Failed to initialize GLAD" << std::endl;
      exit(-1);
    }

    SDL_DisplayMode currentDisplay;
    SDL_GetCurrentDisplayMode(0, &currentDisplay);
    glViewport(0, 0, currentDisplay.w, currentDisplay.h);
}

Queengine::~Queengine() {
  SDL_GL_DeleteContext(this->context);
  SDL_DestroyWindow(this->window);
  SDL_Quit();
}

Queengine *Queengine::GetInstance() {
  if (instance == nullptr) {
    instance = new Queengine();
  }

  return instance;
}

void BindUniforms(Shader *shader) {
  float _resolution = 1.0;
  shader->Set("iResolution", 1, &_resolution);
  shader->Set("iTime", (float) (SDL_GetTicks()/1000.0));
}

void Queengine::Run(unsigned int VAO, vector<Shader> shaders) {

  while (not InputManager::GetInstance().QuitRequested()) {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    InputManager::GetInstance().Update();

    if(InputManager::GetInstance().KeyPress(SDLK_1)){
      shaders[1].active = !shaders[1].active;
    }

    for(int i = 0; i < shaders.size(); i++){
      if(shaders[i].active){
        shaders[i].Use();
        BindUniforms(&shaders[i]);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
      }
    }

    SDL_GL_SwapWindow(this->window);
  }
}
