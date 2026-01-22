#pragma once
#include <map>
#include <SDL.h>


class InputManager
{
	struct KeyData
	{
		bool isDown = false;
		bool isUp = false;
		bool isHeld = false;
	};


public:
	static InputManager& getInstance() {
		static InputManager instance;
		return instance;
	}

	bool HandleInput();

	bool isDown(SDL_Scancode code) { return keys[code].isDown; }
	bool isUp(SDL_Scancode code) { return keys[code].isUp; }
	bool isHeld(SDL_Scancode code) { return keys[code].isHeld; }

protected:
	std::map<SDL_Scancode, KeyData> keys;

	bool isMouseDown = false;
	bool isMouseUp = false;
	bool isMouseHeld = false;
};