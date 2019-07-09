#include "Queengine.h"
#include <iostream>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <fstream>
#include <cmath>
#include <unistd.h>
#include <vector>

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

void BindUniforms(Shader *shader, vector<tuple<Texture, int, int>> textures) {
  glm::vec2 _ifFragCoordOffsetXY(0.0f, 0.0f);
  float _ifFragCoordScale = 1.0f;

  int width, height;
  SDL_DisplayMode currentDisplay;
  SDL_GetCurrentDisplayMode(0, &currentDisplay);
  width = currentDisplay.w;
  height = currentDisplay.h;

  glm::vec3 _resolution(1.0f, 1.0f, 0.5f);
  int mouseX = InputManager::GetInstance().GetMouseX();
  int mouseY = InputManager::GetInstance().GetMouseY();
  int _frame = 0;

  shader->Set("ifFragCoordOffsetUniform", 1, &_ifFragCoordOffsetXY.x);
  shader->Set("iResolution", 1, &_resolution.x);
  shader->Set("iTime", (float) (SDL_GetTicks()/1000.0));
  shader->Set("iGlobalTime", (float) (SDL_GetTicks()/1000.0));
  shader->Set(
    "iMouse",
    mouseX * _resolution[0],
    mouseY * _resolution[0],
    mouseX * _resolution[0],
    mouseY * _resolution[0]
  );
  shader->Set("iFrame", &_frame);

  shader->Set("iChannel0", get<1>(textures[0]));
  // shader->Set("iChannel1", get<1>(textures[1]));
  // shader->Set("iChannel2", get<1>(textures[2]));
  // shader->Set("iChannel3", get<1>(textures[3]));

  glm::mat4 rotation(
      glm::vec4(0.5, 0, -0.9, 0),
      glm::vec4(0, 1.0, 0, 0),
      glm::vec4(0.9, 0, 0.5, 0),
      glm::vec4(0, 0, 0, 1)
  );

  glm::mat4 rotation2(
      glm::vec4(1, 0, 0, 0),
      glm::vec4(0, 0.5, -0.9, 0),
      glm::vec4(0, 0.9, 0.5, 0),
      glm::vec4(0, 0, 0, 1)
  );

  shader->Set("rotation", rotation);
  shader->Set("rotation2", rotation2);
  // shader->Set("material.ambient", 1.0f, 0.5f, 0.31f);
  // shader->Set("material.diffuse", 1.0f, 0.5f, 0.31f);
  // shader->Set("material.specular", 0.5f, 0.5f, 0.5f);
  // shader->Set("material.shininess", 32.0f);
  
  // shader->Set("light.position", 1.2f, 1.0f, 1.0f);
  // shader->Set("light.ambient", 0.2f, 0.2f, 0.2f);
  // shader->Set("light.diffuse", 0.5f, 0.5f, 0.5f);
  // shader->Set("light.specular", 1.0f, 1.0f, 1.0f);
  
}

void Queengine::Run(unsigned int VAO, vector<tuple<Shader, int>> shaderList, vector<tuple<Texture, int, int> > textures) {
  Queengine::Run(VAO, 3, shaderList, textures);
}

void Queengine::Run(unsigned int VAO, int number_of_triangles, vector<tuple<Shader, int>> shaderList, vector<tuple<Texture, int, int>> textures) {
  glEnable(GL_DEPTH_TEST);
  while (not InputManager::GetInstance().QuitRequested()) {
    InputManager::GetInstance().Update();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    InputManager::GetInstance().Update();
    
    this->HandleInput();

    glBindVertexArray(VAO);
    
    for(int i = 0; i < shaderList.size(); i++){
      if(InputManager::GetInstance().KeyPress(get<1>(shaderList[i]))){
        get<0>(shaderList[i]).active = !get<0>(shaderList[i]).active;
      }

      for(int j = 0; j < textures.size(); j++){
        get<0>(textures[j]).use();
        glActiveTexture(get<2>(textures[j]));
      }
      if(get<0>(shaderList[i]).active){
        get<0>(shaderList[i]).Use();
        BindUniforms(&get<0>(shaderList[i]), textures);
      }
    }

    glDrawElements(GL_TRIANGLES, number_of_triangles, GL_UNSIGNED_INT, 0);

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
