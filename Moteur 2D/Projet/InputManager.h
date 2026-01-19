#pragma once
#include <SDL.h>
#include <unordered_map>

struct KeyState
{
    bool isDown;
    bool isRelease;
    bool isHeld;
};

class InputManager
{
private:
    InputManager() {} 
    static InputManager* instance;
    std::unordered_map<SDL_Keycode, KeyState> keysStates;
    std::unordered_map<int, KeyState> mouseButtonsStates;

public:
    static InputManager* GetInstance();


    bool IsKeyDown(SDL_KeyCode key) { return keysStates[SDL_GetKeyFromScancode(SDL_GetScancodeFromKey(key))].isDown; }
    bool IsKeyReleased(SDL_KeyCode key) { return keysStates[SDL_GetKeyFromScancode(SDL_GetScancodeFromKey(key))].isRelease; }
    bool IsKeyHeld(SDL_KeyCode key) { return keysStates[SDL_GetKeyFromScancode(SDL_GetScancodeFromKey(key))].isHeld; }

    bool update();
};