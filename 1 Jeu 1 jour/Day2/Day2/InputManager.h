#pragma once
#include "Vector2D.h"
#include <SDL.h>
#include <unordered_map>
#include <functional>

struct keyState {
	bool isDown;
	bool isRelease;
	bool isHeld;
};



class InputManager
{

private:
	std::unordered_map<SDL_Keycode, keyState> keysStates;

	std::function<void(SDL_Keycode)> m_onKeyDown = nullptr;

public:

	static InputManager& getInstance() {
		static InputManager instance;
		return instance;
	}


	bool IsKeyDown(SDL_KeyCode key) { return keysStates[SDL_GetKeyFromScancode(SDL_GetScancodeFromKey(key))].isDown; }
	bool IsKeyReleased(SDL_KeyCode key) { return keysStates[SDL_GetKeyFromScancode(SDL_GetScancodeFromKey(key))].isRelease; }
	bool IsKeyHeld(SDL_KeyCode key) { return keysStates[SDL_GetKeyFromScancode(SDL_GetScancodeFromKey(key))].isHeld; }


	void resetKey(SDL_KeyCode key) {
		keysStates[SDL_GetKeyFromScancode(SDL_GetScancodeFromKey(key))] = { false,false ,false };
	}
	bool update();
};
