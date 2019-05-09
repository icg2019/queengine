#include "InputManager.h"
#include <cstring>

InputManager::InputManager() {
    memset(this->mouseState, false, sizeof this->mouseState);
    memset(this->mouseUpdate, 0, sizeof this->mouseUpdate);
    this->quitRequested = false;
    this->updateCounter = 0;
    this->mouseX = 0;
    this->mouseY = 0;
}

InputManager::~InputManager() {
  memset(this->mouseState, 0, 6*sizeof(bool));
	memset(this->mouseUpdate, 0, 6*sizeof(int));
  this->quitRequested = false;
  this->updateCounter = 0;
  this->mouseX = 0;
  this->mouseY = 0;
}

bool InputManager::KeyPress(int key) {
  if(keyUpdate[key] == updateCounter)
    return keyState[key];
  
  return false;
}

bool InputManager::KeyRelease(int key) {
  if(keyUpdate[key] == updateCounter)
    return not keyState[key];
  
  return false;
}

void InputManager::Update() {
  SDL_Event event;
  this->updateCounter++;
  SDL_GetMouseState(&(this->mouseX), &(this->mouseY));

  this->mouseX += mouseX;
  this->mouseY += mouseY;

 	while (SDL_PollEvent(&event)) {
    if(not event.key.repeat) {
 		  if(event.type == SDL_KEYDOWN) {
 		  	this->keyState[event.key.keysym.sym] = true;
        this->keyUpdate[event.key.keysym.sym] = this->updateCounter;
 		  }
 		  if( event.type == SDL_KEYUP ) {
 		  	this->keyState[event.key.keysym.sym] = false;
        this->keyUpdate[event.key.keysym.sym] = this->updateCounter;
 		  }
      if(event.type == SDL_MOUSEBUTTONDOWN) {
        this->mouseState[event.button.button] = true;
        this->mouseUpdate[event.button.button] = updateCounter;
      }
      if(event.type == SDL_MOUSEBUTTONUP) {
        this->mouseState[event.button.button] = false;
        this->mouseUpdate[event.button.button] = updateCounter;
      }
      if(event.type == SDL_QUIT) {
        this->quitRequested = true;
      }
    }
 	}
}

bool InputManager::IsKeyDown(int key) {
  return keyState[key];
}

bool InputManager::MousePress(int button) {
  if(mouseUpdate[button] == updateCounter)
    return mouseState[button];
  
  return false;
}

bool InputManager::MouseRelease(int button) {
  if(mouseUpdate[button] == updateCounter)
    return not mouseState[button];
  
  return false;
}

bool InputManager::IsMouseDown(int button) {
  return mouseState[button];
}

int InputManager::GetMouseX() {
  return mouseX;
}

int InputManager::GetMouseY() {
  return mouseY;
}

bool InputManager::QuitRequested() {
  return quitRequested;
}

InputManager& InputManager::GetInstance() {
  static InputManager inputInstance;
  
  return inputInstance;
}