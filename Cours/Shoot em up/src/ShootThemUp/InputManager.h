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
	std::unordered_map<int, keyState> mouseButtonsStates;
	Vector2D mousePos = { 0, 0 };

	std::function<void(SDL_Keycode)> m_onKeyDown = nullptr;
	std::function<void()> m_onFocusLost = nullptr;


public:
	bool windowResized = false;
	int newWidth = 0;
	int newHeight = 0;

public:

	static InputManager& getInstance() {
		static InputManager instance;
		return instance;
	}


	bool IsKeyDown(SDL_KeyCode key) { return keysStates[SDL_GetKeyFromScancode(SDL_GetScancodeFromKey(key))].isDown; }
	bool IsKeyReleased(SDL_KeyCode key) { return keysStates[SDL_GetKeyFromScancode(SDL_GetScancodeFromKey(key))].isRelease; }
	bool IsKeyHeld(SDL_KeyCode key) { return keysStates[SDL_GetKeyFromScancode(SDL_GetScancodeFromKey(key))].isHeld; }

	bool IsMouseDown(int key) { return mouseButtonsStates[key].isDown; }
	bool IsMouseReleased(int key) { return mouseButtonsStates[key].isRelease; }
	bool IsMouseHeld(int key) { return mouseButtonsStates[key].isHeld; }


	void resetKey(SDL_KeyCode key) {
		keysStates[SDL_GetKeyFromScancode(SDL_GetScancodeFromKey(key))] = { false,false ,false };
	}
	void SetKeyDownCB(std::function<void(SDL_Keycode)> cb) { m_onKeyDown = cb; }
	void SetOnFocusLostCb(std::function<void()> cb) { m_onFocusLost = cb; }

	Vector2D getMousePos() const { return mousePos; }

	bool update();
};
