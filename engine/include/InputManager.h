#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#define LEFT_ARROW_KEY SDLK_LEFT
#define RIGHT_ARROW_KEY SDLK_RIGHT
#define UP_ARROW_KEY SDLK_UP
#define DOWN_ARROW_KEY SDLK_DOWN
#define ESCAPE_KEY SDLK_ESCAPE
#define SPACE_KEY SDLK_SPACE
#define LEFT_MOUSE_BUTTON SDL_BUTTON_LEFT
#define RIGHT_MOUSE_BUTTON SDL_BUTTON_RIGHT
#define KEY_1 SDLK_1
#define KEY_2 SDLK_2
#define KEY_3 SDLK_3
#define KEY_4 SDLK_4
#define A_KEY SDLK_a
#define F11_KEY SDLK_F11

#define INCLUDE_SDL

#include "SDL_include.h"

#include <unordered_map>
#include <iostream>

using namespace std;

class InputManager {

  private:
    int mouseX;
    int mouseY;
    int updateCounter;
    int mouseUpdate[6];
    bool mouseState[6];
    bool quitRequested;
    unordered_map<int, bool> keyState;
    unordered_map<int, int> keyUpdate;

    InputManager();
    ~InputManager();

  public:
    void Update();
    int GetMouseX();
    int GetMouseY();
    bool KeyPress(int key);
    bool IsKeyDown(int key);
    bool KeyRelease(int key);
    bool MousePress(int button);
    bool IsMouseDown(int button);
    bool MouseRelease(int button);
    bool QuitRequested();
    static InputManager& GetInstance();

    float GetMouseXCanvasCoord();
    float GetMouseYCanvasCoord();
};

#endif