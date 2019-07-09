#include "Queengine.h"
#include <iostream>
#include <glad/glad.h>
#include <fstream>
#include <cmath>

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
    
    SDL_GetCurrentDisplayMode(0, &(this->currentDisplay));
    this->glCanvasArea = Rect(0, 0, currentDisplay.w, currentDisplay.h);
    glViewport(this->glCanvasArea.x, this->glCanvasArea.y, this->glCanvasArea.w, this->glCanvasArea.h);
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

void ToggleFullscreen(SDL_Window* window) {
    bool isFullscreen = SDL_GetWindowFlags(window) & SDL_WINDOW_FULLSCREEN;
    SDL_SetWindowFullscreen(window, isFullscreen ? 0 : SDL_WINDOW_FULLSCREEN);
}

void Queengine::Run(unsigned int VAO) {
  while (not InputManager::GetInstance().QuitRequested()) {
    InputManager::GetInstance().Update();

    this->HandleInput();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
    SDL_GL_SwapWindow(this->window);
  }
}

Rect Queengine::GetGLCanvasArea() {
  return this->glCanvasArea;
}

void Queengine::HandleInput() {
    if (InputManager::GetInstance().KeyPress(F11_KEY)) {
      ToggleFullscreen(this->window);
    }
    if (InputManager::GetInstance().KeyPress(KEY_1)) {
        // Create Triangle
    }
    if (InputManager::GetInstance().KeyPress(KEY_2)) {
        // Create Square
    }
    if (InputManager::GetInstance().KeyPress(KEY_3)) {
        // Create Circle
    }
}
