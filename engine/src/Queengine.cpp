#include "Queengine.h"
#include <iostream>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
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
  vector<float> _ifFragCoordOffsetXY;
  _ifFragCoordOffsetXY.push_back(0.0f);
  _ifFragCoordOffsetXY.push_back(0.0f);

  float _ifFragCoordScale = 1.0f;

  int width;
  int height;
  SDL_DisplayMode currentDisplay;
  SDL_GetCurrentDisplayMode(0, &currentDisplay);
  width = currentDisplay.w;
  height = currentDisplay.h;

  // vector<float> _resolution;
  // _resolution.push_back(width/_ifFragCoordScale);
  // //_resolution.push_back(1.0f);
  // _resolution.push_back(height/_ifFragCoordScale);
  // //_resolution.push_back(1.0f);
  // _resolution.push_back(1.0f);

  glm::vec3 _resolution(1.0f, 1.0f, 1.0f);
  // float _resolution = -0.00000000001;
  int mouseX = InputManager::GetInstance().GetMouseX();
  int mouseY = InputManager::GetInstance().GetMouseY();
  int _frame = 0;

  // shader->Set("ifFragCoordOffsetUniform", 1, _ifFragCoordOffsetXY);
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

  glm::vec3 _scale(10.0f, 10.0f, 0.0f);
  glm::mat4 modelMatrix = glm::mat4();
  modelMatrix = glm::scale(modelMatrix, _scale);

  // glUniformMatrix4fv("model", 1, GL_FALSE, glm::value_ptr(modelMatrix));
  shader->Set("model", modelMatrix);

  shader->Set("tex1", 0);
  shader->Set("tex2", 1);

}

void Queengine::Run(unsigned int VAO, vector<tuple<Shader, int>> shaderList) {
  Queengine::Run(VAO, 3, shaderList);
}

void Queengine::Run(unsigned int VAO, int number_of_triangles, vector<tuple<Shader, int>> shaderList) {
  while (not InputManager::GetInstance().QuitRequested()) {
    InputManager::GetInstance().Update();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    InputManager::GetInstance().Update();

    for(int i = 0; i < shaderList.size(); i++){
      if(InputManager::GetInstance().KeyPress(get<1>(shaderList[i]))){
        get<0>(shaderList[i]).active = !get<0>(shaderList[i]).active;
      }
      if(get<0>(shaderList[i]).active){
        get<0>(shaderList[i]).Use();
        BindUniforms(&get<0>(shaderList[i]));
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, number_of_triangles, GL_UNSIGNED_INT, 0);
      }
    }

    SDL_GL_SwapWindow(this->window);
  }
}
